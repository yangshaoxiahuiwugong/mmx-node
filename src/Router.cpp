/*
 * Router.cpp
 *
 *  Created on: Dec 17, 2021
 *      Author: mad
 */

#include <mmx/Router.h>
#include <mmx/utils.h>

#include <mmx/Return.hxx>
#include <mmx/Request.hxx>
#include <mmx/Router_get_id.hxx>
#include <mmx/Router_get_id_return.hxx>
#include <mmx/Router_get_peers.hxx>
#include <mmx/Router_get_peers_return.hxx>
#include <mmx/Node_get_height.hxx>
#include <mmx/Node_get_height_return.hxx>
#include <mmx/Node_get_synced_height.hxx>
#include <mmx/Node_get_synced_height_return.hxx>
#include <mmx/Node_get_block.hxx>
#include <mmx/Node_get_block_return.hxx>
#include <mmx/Node_get_block_at.hxx>
#include <mmx/Node_get_block_at_return.hxx>
#include <mmx/Node_get_block_hash.hxx>
#include <mmx/Node_get_block_hash_return.hxx>

#include <vnx/vnx.h>
#include <vnx/NoSuchMethod.hxx>
#include <vnx/OverflowException.hxx>


namespace mmx {

Router::Router(const std::string& _vnx_name)
	:	RouterBase(_vnx_name)
{
	params = get_params();
	port = params->port;
}

void Router::init()
{
	Super::init();
	vnx::open_pipe(vnx_name, this, max_queue_ms);
}

void Router::main()
{
	subscribe(input_vdfs, max_queue_ms);
	subscribe(input_blocks, max_queue_ms);
	subscribe(input_verified_vdfs, max_queue_ms);
	subscribe(input_transactions, max_queue_ms);

	peer_set = seed_peers;

	vnx::File known_peers("known_peers.dat");
	if(known_peers.exists()) {
		std::vector<std::string> peers;
		try {
			known_peers.open("rb");
			vnx::read_generic(known_peers.in, peers);
			known_peers.close();
		}
		catch(const std::exception& ex) {
			log(WARN) << "Failed to read peers from file: " << ex.what();
		}
		peer_set.insert(peers.begin(), peers.end());
	}
	log(INFO) << "Loaded " << peer_set.size() << " known peers";

	node = std::make_shared<NodeAsyncClient>(node_server);
	node->vnx_set_non_blocking(true);
	add_async_client(node);

	threads = new vnx::ThreadPool(num_threads);

	set_timer_millis(query_interval_ms, std::bind(&Router::query, this));
	set_timer_millis(update_interval_ms, std::bind(&Router::update, this));
	set_timer_millis(connect_interval_ms, std::bind(&Router::connect, this));
	set_timer_millis(discover_interval * 1000, std::bind(&Router::discover, this));

	connect();

	Super::main();

	try {
		known_peers.open("wb");
		vnx::write_generic(known_peers.out, peer_set);
		known_peers.close();
	}
	catch(const std::exception& ex) {
		log(WARN) << "Failed to write peers to file: " << ex.what();
	}
}

vnx::Hash64 Router::get_id() const
{
	return vnx_get_id();
}

static
bool is_public_address(const std::string& addr)
{
	if(addr.substr(0, 3) == "10." || addr.substr(0, 4) == "127." || addr.substr(0, 8) == "192.168.") {
		return false;
	}
	return true;
}

template<typename T>
std::vector<T> get_subset(const std::set<T>& candidates, const size_t max_count)
{
	std::set<T> result;
	if(max_count < candidates.size()) {
		// return a random subset
		const std::vector<T> tmp(candidates.begin(), candidates.end());
		for(size_t i = 0; i < 2 * candidates.size() && result.size() < max_count; ++i) {
			result.insert(tmp[vnx::rand64() % tmp.size()]);
		}
	} else {
		result = candidates;
	}
	return std::vector<T>(result.begin(), result.end());
}

std::vector<std::string> Router::get_peers(const uint32_t& max_count) const
{
	std::set<std::string> valid;
	for(const auto& entry : peer_map) {
		const auto& addr = entry.second.address;
		if(is_public_address(addr)) {
			valid.insert(addr);
		}
	}
	return get_subset(valid, max_count);
}

std::vector<std::string> Router::get_known_peers() const
{
	return std::vector<std::string>(peer_set.begin(), peer_set.end());
}

std::vector<std::string> Router::get_connected_peers() const
{
	std::vector<std::string> res;
	for(const auto& entry : peer_map) {
		res.push_back(entry.second.address);
	}
	return res;
}

std::shared_ptr<const PeerInfo> Router::get_peer_info() const
{
	const auto now_ms = vnx::get_wall_time_millis();
	auto info = PeerInfo::create();
	for(const auto& entry : peer_map) {
		const auto& state = entry.second;
		peer_info_t peer;
		peer.address = state.address;
		peer.height = state.height;
		peer.bytes_send = state.bytes_send;
		peer.bytes_recv = state.bytes_recv;
		peer.is_synced = state.is_synced;
		peer.is_blocked = state.is_blocked;
		peer.is_outbound = state.is_outbound;
		peer.recv_timeout_ms = now_ms - state.last_receive_ms;
		info->peers.push_back(peer);
	}
	std::sort(info->peers.begin(), info->peers.end(),
		[](const peer_info_t& lhs, const peer_info_t& rhs) -> bool {
			return lhs.address < rhs.address;
		});
	return info;
}

void Router::get_blocks_at_async(const uint32_t& height, const vnx::request_id_t& request_id) const
{
	auto& job = sync_jobs[request_id];
	job.height = height;
	job.start_time_ms = vnx::get_wall_time_millis();
	((Router*)this)->process();
}

void Router::handle(std::shared_ptr<const Block> block)
{
	if(seen_hashes.insert(block->hash).second) {
		if(block->proof) {
			log(INFO) << "Broadcasting block " << block->height;
			send_all(block);
		}
	}
}

void Router::handle(std::shared_ptr<const Transaction> tx)
{
	if(seen_hashes.insert(tx->id).second) {
		log(INFO) << "Broadcasting transaction " << tx->id;
		send_all(tx);
	}
}

void Router::handle(std::shared_ptr<const ProofOfTime> proof)
{
	const auto vdf_iters = proof->start + proof->get_num_iters();

	if(vnx_sample->topic == input_vdfs)
	{
		if(vdf_iters > verified_vdf_iters) {
			if(seen_hashes.insert(proof->calc_hash()).second) {
				log(INFO) << "Broadcasting VDF for " << vdf_iters;
				send_all(proof);
			}
		}
	}
	else if(vnx_sample->topic == input_verified_vdfs)
	{
		verified_vdf_iters = std::max(vdf_iters, verified_vdf_iters);
	}
}

uint32_t Router::send_request(uint64_t client, std::shared_ptr<const vnx::Value> method)
{
	auto req = Request::create();
	req->id = next_request_id++;
	req->method = method;
	send_to(client, req);
	return req->id;
}

void Router::update()
{
	const auto now_ms = vnx::get_wall_time_millis();

	// check if we lost sync due to response timeout
	size_t num_peers = 0;
	for(const auto& entry : peer_map) {
		const auto& peer = entry.second;
		if(peer.is_synced && now_ms - peer.last_receive_ms < sync_loss_delay * 1000) {
			num_peers++;
		}
	}
	if(num_peers < min_sync_peers) {
		if(is_connected) {
			log(WARN) << "Lost sync with network due to timeout!";
			is_connected = false;
			node->start_sync();
		}
	} else {
		is_connected = true;
	}

	// check if we lost sync due to height difference
	node->get_synced_height(
		[this](const vnx::optional<uint32_t>& sync_height) {
			if(sync_height) {
				node_height = *sync_height;
				size_t num_ahead = 0;
				for(const auto& entry : peer_map) {
					const auto& peer = entry.second;
					if(peer.is_synced && peer.height > node_height && peer.height - node_height > params->finality_delay) {
						num_ahead++;
					}
				}
				if(num_ahead >= std::min<size_t>(synced_peers.size(), 1)) {
					log(WARN) << "Lost sync with network due to height difference!";
					node->start_sync();
				}
			}
			is_synced = sync_height;
		});

	// check for sync job timeouts
	for(auto& entry : sync_jobs) {
		auto& job = entry.second;
		if(now_ms - job.start_time_ms > fetch_timeout_ms) {
			if(job.state == FETCH_BLOCKS) {
				job.failed.clear();
			}
			job.pending.clear();
			job.start_time_ms = now_ms;
			if(synced_peers.size() >= min_sync_peers) {
				log(WARN) << "Timeout on sync job for height " << job.height << ", trying again ...";
			}
		}
	}

	process();
}

bool Router::process(std::shared_ptr<const Return> ret)
{
	const auto now_ms = vnx::get_wall_time_millis();

	bool did_consume = false;
	for(auto iter = sync_jobs.begin(); iter != sync_jobs.end();)
	{
		auto& job = iter->second;
		if(ret) {
			// check for any returns
			auto iter = job.request_map.find(ret->id);
			if(iter != job.request_map.end()) {
				if(auto result = std::dynamic_pointer_cast<const Node_get_block_hash_return>(ret->result)) {
					if(auto hash = result->_ret_0) {
						job.hash_map[*hash].insert(iter->second);
						job.succeeded.insert(iter->second);
					} else {
						job.failed.insert(iter->second);
					}
				}
				else if(auto result = std::dynamic_pointer_cast<const Node_get_block_return>(ret->result)) {
					if(auto block = result->_ret_0) {
						job.blocks[block->hash] = block;
						job.succeeded.insert(iter->second);
					} else {
						job.failed.insert(iter->second);
					}
				}
				else if(auto result = std::dynamic_pointer_cast<const vnx::OverflowException>(ret->result)) {
					// try again
				}
				else {
					job.failed.insert(iter->second);
				}
				job.pending.erase(iter->second);
				job.request_map.erase(iter);
				did_consume = true;
			}
		}
		const auto num_peers_try = std::min<size_t>(max_sync_peers, std::max<size_t>(synced_peers.size(), min_sync_peers));

		if(job.state == FETCH_HASHES)
		{
			if(job.succeeded.size() < min_sync_peers
				&& job.succeeded.size() + job.failed.size() < num_peers_try)
			{
				for(auto client : synced_peers) {
					if(job.succeeded.size() + job.pending.size() + job.failed.size() >= max_sync_peers) {
						break;
					}
					if(!job.succeeded.count(client) && !job.pending.count(client) && !job.failed.count(client))
					{
						auto req = Node_get_block_hash::create();
						req->height = job.height;
						const auto id = send_request(client, req);
						job.request_map[id] = client;
						job.pending.insert(client);
					}
				}
			} else {
				log(DEBUG) << "Got " << job.hash_map.size() << " block hashes for height "
						<< job.height << " from " << job.succeeded.size() << " peers, " << job.failed.size() << " failed";
				job.failed.clear();
				job.pending.clear();
				job.succeeded.clear();
				job.request_map.clear();
				job.state = FETCH_BLOCKS;
				job.start_time_ms = now_ms;
			}
		}
		if(job.state == FETCH_BLOCKS)
		{
			if(job.blocks.size() < job.hash_map.size()
				&& (job.succeeded.size() + job.failed.size() < num_peers_try || job.blocks.empty()))
			{
				for(const auto& entry : job.hash_map) {
					if(!job.blocks.count(entry.first))
					{
						size_t num_pending = 0;
						for(auto client : entry.second) {
							if(job.pending.count(client)) {
								num_pending++;
							}
						}
						const auto max_pending = std::max<size_t>((now_ms - job.start_time_ms) / update_interval_ms, 1);
						if(num_pending < max_pending)
						{
							auto clients = entry.second;
							for(auto id : job.failed) {
								clients.erase(id);
							}
							for(auto id : job.pending) {
								clients.erase(id);
							}
							for(auto client : get_subset(clients, max_pending - num_pending))
							{
								auto req = Node_get_block::create();
								req->hash = entry.first;
								const auto id = send_request(client, req);
								job.request_map[id] = client;
								job.pending.insert(client);
							}
						}
					}
				}
			} else {
				if(!job.hash_map.empty()) {
					log(DEBUG) << "Got " << job.blocks.size() << " / " << job.hash_map.size() << " blocks for height " << job.height << " by fetching "
							<< job.succeeded.size() + job.pending.size() + job.failed.size() << " times, " << job.failed.size() << " failed";
				}
				// we are done with the job
				std::vector<std::shared_ptr<const Block>> blocks;
				for(const auto& entry : job.blocks) {
					blocks.push_back(entry.second);
				}
				get_blocks_at_async_return(iter->first, blocks);
				iter = sync_jobs.erase(iter);
				continue;
			}
		}
		iter++;
	}
	return did_consume;
}

void Router::connect()
{
	for(const auto& address : peer_set)
	{
		if(synced_peers.size() >= num_peers_out || connecting_peers.size() >= num_threads) {
			break;
		}
		if(connecting_peers.count(address) || block_peers.count(address)) {
			continue;
		}
		bool connected = false;
		for(const auto& entry : peer_map) {
			if(address == entry.second.address) {
				connected = true;
			}
		}
		if(connected) {
			continue;
		}
		log(DEBUG) << "Trying to connect to " << address;

		connecting_peers.insert(address);
		threads->add_task(std::bind(&Router::connect_task, this, address));
	}
}

void Router::query()
{
	auto req = Request::create();
	req->id = next_request_id++;
	req->method = Node_get_synced_height::create();
	send_all(req);
}

void Router::discover()
{
	auto method = Router_get_peers::create();
	method->max_count = num_peers_out;
	auto req = Request::create();
	req->id = next_request_id++;
	req->method = method;
	send_all(req);
}

void Router::add_peer(const std::string& address, const int sock)
{
	connecting_peers.erase(address);

	if(sock >= 0) {
		if(synced_peers.size() >= num_peers_out) {
			vnx::TcpEndpoint().close(sock);
			return;
		}
		const auto client = add_client(sock, address);

		auto& peer = peer_map[client];
		peer.is_outbound = true;

		send_request(client, Router_get_id::create());
		send_request(client, Node_get_synced_height::create());
	}
	else if(!seed_peers.count(address)) {
		peer_set.erase(address);
	}
}

void Router::connect_task(const std::string& address) noexcept
{
	vnx::TcpEndpoint peer;
	peer.host_name = address;
	peer.port = params->port;
	auto sock = peer.open();
	try {
		peer.connect(sock);
	}
	catch(const std::exception& ex) {
		if(show_warnings) {
			log(WARN) << "Connecting to peer " << address << " failed with: " << ex.what();
		}
		peer.close(sock);
		sock = -1;
	}
	if(vnx::do_run()) {
		add_task(std::bind(&Router::add_peer, this, address, sock));
	}
}

void Router::print_stats()
{
	log(INFO) << float(tx_counter * 1000) / stats_interval_ms
			  << " tx/s, " << float(vdf_counter * 1000) / stats_interval_ms
			  << " vdf/s, " << float(block_counter * 1000) / stats_interval_ms
			  << " blocks/s, " << synced_peers.size() << " / " <<  peer_map.size() << " / " << peer_set.size()
			  << " peers, " << upload_counter << " blocks sent";
	tx_counter = 0;
	vdf_counter = 0;
	block_counter = 0;
}

void Router::on_vdf(uint64_t client, std::shared_ptr<const ProofOfTime> proof)
{
	if(!seen_hashes.insert(proof->calc_hash()).second) {
		return;
	}
	publish(proof, output_vdfs);
	relay(client, proof);
	vdf_counter++;
}

void Router::on_block(uint64_t client, std::shared_ptr<const Block> block)
{
	if(!seen_hashes.insert(block->hash).second) {
		return;
	}
	if(!block->is_valid()) {
		return;
	}
	publish(block, output_blocks);
	relay(client, block);
	block_counter++;
}

void Router::on_transaction(uint64_t client, std::shared_ptr<const Transaction> tx)
{
	if(!seen_hashes.insert(tx->id).second) {
		return;
	}
	if(!tx->is_valid()) {
		return;
	}
	relay(client, tx);
	publish(tx, output_transactions);
	tx_counter++;
}

void Router::relay(uint64_t source, std::shared_ptr<const vnx::Value> msg)
{
	for(auto& entry : peer_map) {
		auto& peer = entry.second;
		if(!peer.is_blocked && entry.first != source) {
			send_to(peer, msg);
		}
	}
}

void Router::send_to(uint64_t client, std::shared_ptr<const vnx::Value> msg)
{
	if(auto peer = find_peer(client)) {
		send_to(*peer, msg);
	}
}

void Router::send_to(peer_t& peer, std::shared_ptr<const vnx::Value> msg)
{
	auto& out = peer.out;
	vnx::write(out, uint16_t(vnx::CODE_UINT32));
	vnx::write(out, uint32_t(0));
	vnx::write(out, msg);
	out.flush();

	auto buffer = std::make_shared<vnx::Buffer>(peer.data);
	peer.data.clear();

	if(buffer->size() > max_msg_size) {
		return;
	}
	*((uint32_t*)buffer->data(2)) = buffer->size() - 6;

	peer.bytes_send += buffer->size();
	Super::send_to(peer.client, buffer);
}

void Router::send_all(std::shared_ptr<const vnx::Value> msg)
{
	for(auto& entry : peer_map) {
		send_to(entry.second, msg);
	}
}

template<typename R, typename T>
void Router::send_result(uint64_t client, uint32_t id, const T& value)
{
	auto ret = Return::create();
	ret->id = id;
	auto result = R::create();
	result->_ret_0 = value;
	ret->result = result;
	send_to(client, ret);
}

void Router::on_error(uint64_t client, uint32_t id, const vnx::exception& ex)
{
	auto ret = Return::create();
	ret->id = id;
	ret->result = ex.value();
	send_to(client, ret);
}

void Router::on_request(uint64_t client, std::shared_ptr<const Request> msg)
{
	const auto method = msg->method;
	if(!method) {
		return;
	}
	switch(method->get_type_hash())
	{
		case Router_get_id::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Router_get_id>(method)) {
				send_result<Router_get_id_return>(client, msg->id, get_id());
			}
			break;
		case Router_get_peers::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Router_get_peers>(method)) {
				send_result<Router_get_peers_return>(client, msg->id, get_peers(value->max_count));
			}
			break;
		case Node_get_height::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_height>(method)) {
				node->get_height(
						[=](const uint32_t& height) {
							send_result<Node_get_height_return>(client, msg->id, height);
						},
						std::bind(&Router::on_error, this, client, msg->id, std::placeholders::_1));
			}
			break;
		case Node_get_synced_height::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_synced_height>(method)) {
				node->get_synced_height(
						[=](const vnx::optional<uint32_t>& height) {
							send_result<Node_get_synced_height_return>(client, msg->id, height);
						},
						std::bind(&Router::on_error, this, client, msg->id, std::placeholders::_1));
			}
			break;
		case Node_get_block::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_block>(method)) {
				node->get_block(value->hash,
						[=](std::shared_ptr<const Block> block) {
							upload_counter++;
							send_result<Node_get_block_return>(client, msg->id, block);
						},
						std::bind(&Router::on_error, this, client, msg->id, std::placeholders::_1));
			}
			break;
		case Node_get_block_at::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_block_at>(method)) {
				node->get_block_at(value->height,
						[=](std::shared_ptr<const Block> block) {
							upload_counter++;
							send_result<Node_get_block_at_return>(client, msg->id, block);
						},
						std::bind(&Router::on_error, this, client, msg->id, std::placeholders::_1));
			}
			break;
		case Node_get_block_hash::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_block_hash>(method)) {
				node->get_block_hash(value->height,
						[=](const vnx::optional<hash_t>& hash) {
							send_result<Node_get_block_hash_return>(client, msg->id, hash);
						},
						std::bind(&Router::on_error, this, client, msg->id, std::placeholders::_1));
			}
			break;
		default: {
			auto ret = Return::create();
			ret->id = msg->id;
			ret->result = vnx::NoSuchMethod::create();
			send_to(client, ret);
		}
	}
}

void Router::on_return(uint64_t client, std::shared_ptr<const Return> msg)
{
	if(process(msg)) {
		return;
	}
	const auto result = msg->result;
	if(!result) {
		return;
	}
	switch(result->get_type_hash())
	{
		case Router_get_id_return::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Router_get_id_return>(result)) {
				if(auto peer = find_peer(client)) {
					peer->node_id = value->_ret_0;
					if(value->_ret_0 == get_id()) {
						log(INFO) << "Discovered our own address: " << peer->address;
						self_addrs.insert(peer->address);
						block_peers.insert(peer->address);
						disconnect(client);
					}
				}
			}
			break;
		case Router_get_peers_return::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Router_get_peers_return>(result)) {
				peer_set.insert(value->_ret_0.begin(), value->_ret_0.end());
			}
			break;
		case Node_get_height_return::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_height_return>(result)) {
				if(auto peer = find_peer(client)) {
					peer->height = value->_ret_0;
					peer->last_receive_ms = vnx::get_wall_time_millis();
				}
			}
			break;
		case Node_get_synced_height_return::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_synced_height_return>(result)) {
				if(auto peer = find_peer(client)) {
					if(auto height = value->_ret_0) {
						if(!peer->is_synced) {
							log(INFO) << "Peer " << peer->address << " is synced at height " << *height;
						}
						peer->height = *height;
						peer->is_synced = true;
						synced_peers.insert(client);

						if(is_synced
							&& peer->height >= node_height - 1
							&& peer->height <= node_height + params->finality_delay)
						{
							// check their previous block hash
							auto req = Node_get_block_hash::create();
							req->height = node_height - 1;
							peer->hash_check.height = req->height;
							peer->hash_check.request = send_request(client, req);
						}
					}
					else {
						if(peer->is_synced) {
							log(INFO) << "Peer " << peer->address << " is not synced";
						}
						peer->is_synced = false;
						synced_peers.erase(client);

						// check their height
						send_request(client, Node_get_height::create());
					}
					peer->last_receive_ms = vnx::get_wall_time_millis();
				}
			}
			break;
		case Node_get_block_hash_return::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_block_hash_return>(result)) {
				if(auto peer = find_peer(client)) {
					if(peer->hash_check.request == msg->id && value->_ret_0)
					{
						const auto height = peer->hash_check.height;
						const auto peer_hash = *value->_ret_0;
						node->get_block(peer_hash,
							[this, client, height, peer_hash](std::shared_ptr<const Block> block) {
								if(!block) {
									auto req = Node_get_block::create();
									req->hash = peer_hash;
									send_request(client, req);
									log(WARN) << "Fetching unknown block at height " << height << " with hash " << peer_hash;
								}
							});
					}
				}
			}
			break;
		case Node_get_block_return::VNX_TYPE_ID:
			if(auto value = std::dynamic_pointer_cast<const Node_get_block_return>(result)) {
				if(auto block = value->_ret_0) {
					if(is_synced && block->height + params->finality_delay >= node_height)
					{
						// check if we have previous block
						const auto next = block;
						node->get_block(block->prev,
							[this, client, next](std::shared_ptr<const Block> block) {
								if(!block) {
									auto req = Node_get_block::create();
									req->hash = next->prev;
									send_request(client, req);
									log(WARN) << "Fetching unknown block at height " << next->height - 1 << " with hash " << next->prev;
								}
							});
					}
					node->add_block(block);
				}
			}
			break;
	}
}

void Router::on_msg(uint64_t client, std::shared_ptr<const vnx::Value> msg)
{
	switch(msg->get_type_hash())
	{
	case ProofOfTime::VNX_TYPE_ID:
		if(auto value = std::dynamic_pointer_cast<const ProofOfTime>(msg)) {
			on_vdf(client, value);
		}
		break;
	case Block::VNX_TYPE_ID:
		if(auto value = std::dynamic_pointer_cast<const Block>(msg)) {
			on_block(client, value);
		}
		break;
	case Transaction::VNX_TYPE_ID:
		if(auto value = std::dynamic_pointer_cast<const Transaction>(msg)) {
			on_transaction(client, value);
		}
		break;
	case Request::VNX_TYPE_ID:
		if(auto value = std::dynamic_pointer_cast<const Request>(msg)) {
			on_request(client, value);
		}
		break;
	case Return::VNX_TYPE_ID:
		if(auto value = std::dynamic_pointer_cast<const Return>(msg)) {
			on_return(client, value);
		}
		break;
	}
}

void Router::on_buffer(uint64_t client, void*& buffer, size_t& max_bytes)
{
	auto& peer = get_peer(client);
	const auto offset = peer.buffer.size();
	if(peer.msg_size == 0) {
		if(offset > 6) {
			throw std::logic_error("offset > 6");
		}
		peer.buffer.reserve(6);
		max_bytes = 6 - offset;
	} else {
		max_bytes = (6 + peer.msg_size) - offset;
	}
	buffer = peer.buffer.data(offset);
}

bool Router::on_read(uint64_t client, size_t num_bytes)
{
	auto& peer = get_peer(client);
	peer.bytes_recv += num_bytes;
	peer.buffer.resize(peer.buffer.size() + num_bytes);

	if(peer.msg_size == 0) {
		if(peer.buffer.size() >= 6) {
			uint16_t code = 0;
			vnx::read_value(peer.buffer.data(), code);
			vnx::read_value(peer.buffer.data(2), peer.msg_size, &code);
			if(peer.msg_size > max_msg_size) {
				throw std::logic_error("message too large");
			}
			if(peer.msg_size > 0) {
				peer.buffer.reserve(6 + peer.msg_size);
			} else {
				peer.buffer.clear();
			}
		}
	}
	else if(peer.buffer.size() == 6 + peer.msg_size)
	{
		peer.in.read(6);
		if(auto value = vnx::read(peer.in)) {
			try {
				on_msg(client, value);
			}
			catch(const std::exception& ex) {
				if(show_warnings) {
					log(WARN) << "on_msg() failed with: " << ex.what();
				}
			}
		}
		peer.buffer.clear();
		peer.in_stream.reset();
		peer.msg_size = 0;
	}
	return true;
}

void Router::on_pause(uint64_t client)
{
	auto& peer = get_peer(client);
	peer.is_blocked = true;

	if(!peer.is_outbound) {
		pause(client);		// pause incoming traffic
	}
}

void Router::on_resume(uint64_t client)
{
	auto& peer = get_peer(client);
	peer.is_blocked = false;

	if(!peer.is_outbound) {
		resume(client);		// resume incoming traffic
	}
}

void Router::on_connect(uint64_t client, const std::string& address)
{
	if(block_peers.count(address)) {
		disconnect(client);
		return;
	}
	auto& peer = peer_map[client];
	peer.client = client;
	peer.address = address;
	peer_set.insert(address);

	log(INFO) << "Connected to peer " << peer.address;
}

void Router::on_disconnect(uint64_t client)
{
	if(!vnx_task) {
		// cannot modify peer_map in a nested loop
		add_task(std::bind(&Router::on_disconnect, this, client));
		return;
	}
	auto iter = peer_map.find(client);
	if(iter != peer_map.end()) {
		log(INFO) << "Peer " << iter->second.address << " disconnected";
		peer_map.erase(iter);
	}
	synced_peers.erase(client);
}

Router::peer_t& Router::get_peer(uint64_t client)
{
	if(auto peer = find_peer(client)) {
		return *peer;
	}
	throw std::logic_error("no such peer");
}

Router::peer_t* Router::find_peer(uint64_t client)
{
	auto iter = peer_map.find(client);
	if(iter != peer_map.end()) {
		return &iter->second;
	}
	return nullptr;
}


} // mmx
