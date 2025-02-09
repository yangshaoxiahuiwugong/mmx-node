
// AUTO GENERATED by vnxcppcodegen

#include <mmx/package.hxx>
#include <mmx/NodeBase.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <mmx/Block.hxx>
#include <mmx/BlockHeader.hxx>
#include <mmx/Contract.hxx>
#include <mmx/Node_add_block.hxx>
#include <mmx/Node_add_block_return.hxx>
#include <mmx/Node_add_transaction.hxx>
#include <mmx/Node_add_transaction_return.hxx>
#include <mmx/Node_get_balance.hxx>
#include <mmx/Node_get_balance_return.hxx>
#include <mmx/Node_get_block.hxx>
#include <mmx/Node_get_block_return.hxx>
#include <mmx/Node_get_block_at.hxx>
#include <mmx/Node_get_block_at_return.hxx>
#include <mmx/Node_get_block_hash.hxx>
#include <mmx/Node_get_block_hash_return.hxx>
#include <mmx/Node_get_contract.hxx>
#include <mmx/Node_get_contract_return.hxx>
#include <mmx/Node_get_header_at.hxx>
#include <mmx/Node_get_header_at_return.hxx>
#include <mmx/Node_get_height.hxx>
#include <mmx/Node_get_height_return.hxx>
#include <mmx/Node_get_stxo_list.hxx>
#include <mmx/Node_get_stxo_list_return.hxx>
#include <mmx/Node_get_synced_height.hxx>
#include <mmx/Node_get_synced_height_return.hxx>
#include <mmx/Node_get_total_balance.hxx>
#include <mmx/Node_get_total_balance_return.hxx>
#include <mmx/Node_get_transaction.hxx>
#include <mmx/Node_get_transaction_return.hxx>
#include <mmx/Node_get_tx_key.hxx>
#include <mmx/Node_get_tx_key_return.hxx>
#include <mmx/Node_get_txo_info.hxx>
#include <mmx/Node_get_txo_info_return.hxx>
#include <mmx/Node_get_utxo_list.hxx>
#include <mmx/Node_get_utxo_list_return.hxx>
#include <mmx/Node_start_sync.hxx>
#include <mmx/Node_start_sync_return.hxx>
#include <mmx/ProofOfTime.hxx>
#include <mmx/ProofResponse.hxx>
#include <mmx/Transaction.hxx>
#include <mmx/addr_t.hpp>
#include <mmx/hash_t.hpp>
#include <mmx/stxo_entry_t.hxx>
#include <mmx/tx_key_t.hxx>
#include <mmx/txio_key_t.hxx>
#include <mmx/txo_info_t.hxx>
#include <mmx/utxo_entry_t.hxx>
#include <vnx/Module.h>
#include <vnx/ModuleInterface_vnx_get_config.hxx>
#include <vnx/ModuleInterface_vnx_get_config_return.hxx>
#include <vnx/ModuleInterface_vnx_get_config_object.hxx>
#include <vnx/ModuleInterface_vnx_get_config_object_return.hxx>
#include <vnx/ModuleInterface_vnx_get_module_info.hxx>
#include <vnx/ModuleInterface_vnx_get_module_info_return.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code.hxx>
#include <vnx/ModuleInterface_vnx_get_type_code_return.hxx>
#include <vnx/ModuleInterface_vnx_restart.hxx>
#include <vnx/ModuleInterface_vnx_restart_return.hxx>
#include <vnx/ModuleInterface_vnx_self_test.hxx>
#include <vnx/ModuleInterface_vnx_self_test_return.hxx>
#include <vnx/ModuleInterface_vnx_set_config.hxx>
#include <vnx/ModuleInterface_vnx_set_config_return.hxx>
#include <vnx/ModuleInterface_vnx_set_config_object.hxx>
#include <vnx/ModuleInterface_vnx_set_config_object_return.hxx>
#include <vnx/ModuleInterface_vnx_stop.hxx>
#include <vnx/ModuleInterface_vnx_stop_return.hxx>
#include <vnx/TopicPtr.hpp>
#include <vnx/addons/HttpComponent_http_request.hxx>
#include <vnx/addons/HttpComponent_http_request_return.hxx>
#include <vnx/addons/HttpComponent_http_request_chunk.hxx>
#include <vnx/addons/HttpComponent_http_request_chunk_return.hxx>
#include <vnx/addons/HttpData.hxx>
#include <vnx/addons/HttpRequest.hxx>
#include <vnx/addons/HttpResponse.hxx>

#include <vnx/vnx.h>


namespace mmx {


const vnx::Hash64 NodeBase::VNX_TYPE_HASH(0x289d7651582d76a3ull);
const vnx::Hash64 NodeBase::VNX_CODE_HASH(0xc10445207d1d4e71ull);

NodeBase::NodeBase(const std::string& _vnx_name)
	:	Module::Module(_vnx_name)
{
	vnx::read_config(vnx_name + ".input_vdfs", input_vdfs);
	vnx::read_config(vnx_name + ".input_blocks", input_blocks);
	vnx::read_config(vnx_name + ".input_transactions", input_transactions);
	vnx::read_config(vnx_name + ".input_timelord_vdfs", input_timelord_vdfs);
	vnx::read_config(vnx_name + ".input_harvester_proof", input_harvester_proof);
	vnx::read_config(vnx_name + ".output_verified_vdfs", output_verified_vdfs);
	vnx::read_config(vnx_name + ".output_verified_blocks", output_verified_blocks);
	vnx::read_config(vnx_name + ".output_committed_blocks", output_committed_blocks);
	vnx::read_config(vnx_name + ".output_transactions", output_transactions);
	vnx::read_config(vnx_name + ".output_interval_request", output_interval_request);
	vnx::read_config(vnx_name + ".output_timelord_infuse", output_timelord_infuse);
	vnx::read_config(vnx_name + ".output_challenges", output_challenges);
	vnx::read_config(vnx_name + ".max_queue_ms", max_queue_ms);
	vnx::read_config(vnx_name + ".update_interval_ms", update_interval_ms);
	vnx::read_config(vnx_name + ".max_history", max_history);
	vnx::read_config(vnx_name + ".replay_height", replay_height);
	vnx::read_config(vnx_name + ".max_sync_jobs", max_sync_jobs);
	vnx::read_config(vnx_name + ".num_sync_retries", num_sync_retries);
	vnx::read_config(vnx_name + ".opencl_device", opencl_device);
	vnx::read_config(vnx_name + ".do_sync", do_sync);
	vnx::read_config(vnx_name + ".storage_path", storage_path);
	vnx::read_config(vnx_name + ".router_name", router_name);
	vnx::read_config(vnx_name + ".timelord_name", timelord_name);
}

vnx::Hash64 NodeBase::get_type_hash() const {
	return VNX_TYPE_HASH;
}

std::string NodeBase::get_type_name() const {
	return "mmx.Node";
}

const vnx::TypeCode* NodeBase::get_type_code() const {
	return mmx::vnx_native_type_code_NodeBase;
}

void NodeBase::accept(vnx::Visitor& _visitor) const {
	const vnx::TypeCode* _type_code = mmx::vnx_native_type_code_NodeBase;
	_visitor.type_begin(*_type_code);
	_visitor.type_field(_type_code->fields[0], 0); vnx::accept(_visitor, input_vdfs);
	_visitor.type_field(_type_code->fields[1], 1); vnx::accept(_visitor, input_blocks);
	_visitor.type_field(_type_code->fields[2], 2); vnx::accept(_visitor, input_transactions);
	_visitor.type_field(_type_code->fields[3], 3); vnx::accept(_visitor, input_timelord_vdfs);
	_visitor.type_field(_type_code->fields[4], 4); vnx::accept(_visitor, input_harvester_proof);
	_visitor.type_field(_type_code->fields[5], 5); vnx::accept(_visitor, output_verified_vdfs);
	_visitor.type_field(_type_code->fields[6], 6); vnx::accept(_visitor, output_verified_blocks);
	_visitor.type_field(_type_code->fields[7], 7); vnx::accept(_visitor, output_committed_blocks);
	_visitor.type_field(_type_code->fields[8], 8); vnx::accept(_visitor, output_transactions);
	_visitor.type_field(_type_code->fields[9], 9); vnx::accept(_visitor, output_interval_request);
	_visitor.type_field(_type_code->fields[10], 10); vnx::accept(_visitor, output_timelord_infuse);
	_visitor.type_field(_type_code->fields[11], 11); vnx::accept(_visitor, output_challenges);
	_visitor.type_field(_type_code->fields[12], 12); vnx::accept(_visitor, max_queue_ms);
	_visitor.type_field(_type_code->fields[13], 13); vnx::accept(_visitor, update_interval_ms);
	_visitor.type_field(_type_code->fields[14], 14); vnx::accept(_visitor, max_history);
	_visitor.type_field(_type_code->fields[15], 15); vnx::accept(_visitor, replay_height);
	_visitor.type_field(_type_code->fields[16], 16); vnx::accept(_visitor, max_sync_jobs);
	_visitor.type_field(_type_code->fields[17], 17); vnx::accept(_visitor, num_sync_retries);
	_visitor.type_field(_type_code->fields[18], 18); vnx::accept(_visitor, opencl_device);
	_visitor.type_field(_type_code->fields[19], 19); vnx::accept(_visitor, do_sync);
	_visitor.type_field(_type_code->fields[20], 20); vnx::accept(_visitor, storage_path);
	_visitor.type_field(_type_code->fields[21], 21); vnx::accept(_visitor, router_name);
	_visitor.type_field(_type_code->fields[22], 22); vnx::accept(_visitor, timelord_name);
	_visitor.type_end(*_type_code);
}

void NodeBase::write(std::ostream& _out) const {
	_out << "{";
	_out << "\"input_vdfs\": "; vnx::write(_out, input_vdfs);
	_out << ", \"input_blocks\": "; vnx::write(_out, input_blocks);
	_out << ", \"input_transactions\": "; vnx::write(_out, input_transactions);
	_out << ", \"input_timelord_vdfs\": "; vnx::write(_out, input_timelord_vdfs);
	_out << ", \"input_harvester_proof\": "; vnx::write(_out, input_harvester_proof);
	_out << ", \"output_verified_vdfs\": "; vnx::write(_out, output_verified_vdfs);
	_out << ", \"output_verified_blocks\": "; vnx::write(_out, output_verified_blocks);
	_out << ", \"output_committed_blocks\": "; vnx::write(_out, output_committed_blocks);
	_out << ", \"output_transactions\": "; vnx::write(_out, output_transactions);
	_out << ", \"output_interval_request\": "; vnx::write(_out, output_interval_request);
	_out << ", \"output_timelord_infuse\": "; vnx::write(_out, output_timelord_infuse);
	_out << ", \"output_challenges\": "; vnx::write(_out, output_challenges);
	_out << ", \"max_queue_ms\": "; vnx::write(_out, max_queue_ms);
	_out << ", \"update_interval_ms\": "; vnx::write(_out, update_interval_ms);
	_out << ", \"max_history\": "; vnx::write(_out, max_history);
	_out << ", \"replay_height\": "; vnx::write(_out, replay_height);
	_out << ", \"max_sync_jobs\": "; vnx::write(_out, max_sync_jobs);
	_out << ", \"num_sync_retries\": "; vnx::write(_out, num_sync_retries);
	_out << ", \"opencl_device\": "; vnx::write(_out, opencl_device);
	_out << ", \"do_sync\": "; vnx::write(_out, do_sync);
	_out << ", \"storage_path\": "; vnx::write(_out, storage_path);
	_out << ", \"router_name\": "; vnx::write(_out, router_name);
	_out << ", \"timelord_name\": "; vnx::write(_out, timelord_name);
	_out << "}";
}

void NodeBase::read(std::istream& _in) {
	if(auto _json = vnx::read_json(_in)) {
		from_object(_json->to_object());
	}
}

vnx::Object NodeBase::to_object() const {
	vnx::Object _object;
	_object["__type"] = "mmx.Node";
	_object["input_vdfs"] = input_vdfs;
	_object["input_blocks"] = input_blocks;
	_object["input_transactions"] = input_transactions;
	_object["input_timelord_vdfs"] = input_timelord_vdfs;
	_object["input_harvester_proof"] = input_harvester_proof;
	_object["output_verified_vdfs"] = output_verified_vdfs;
	_object["output_verified_blocks"] = output_verified_blocks;
	_object["output_committed_blocks"] = output_committed_blocks;
	_object["output_transactions"] = output_transactions;
	_object["output_interval_request"] = output_interval_request;
	_object["output_timelord_infuse"] = output_timelord_infuse;
	_object["output_challenges"] = output_challenges;
	_object["max_queue_ms"] = max_queue_ms;
	_object["update_interval_ms"] = update_interval_ms;
	_object["max_history"] = max_history;
	_object["replay_height"] = replay_height;
	_object["max_sync_jobs"] = max_sync_jobs;
	_object["num_sync_retries"] = num_sync_retries;
	_object["opencl_device"] = opencl_device;
	_object["do_sync"] = do_sync;
	_object["storage_path"] = storage_path;
	_object["router_name"] = router_name;
	_object["timelord_name"] = timelord_name;
	return _object;
}

void NodeBase::from_object(const vnx::Object& _object) {
	for(const auto& _entry : _object.field) {
		if(_entry.first == "do_sync") {
			_entry.second.to(do_sync);
		} else if(_entry.first == "input_blocks") {
			_entry.second.to(input_blocks);
		} else if(_entry.first == "input_harvester_proof") {
			_entry.second.to(input_harvester_proof);
		} else if(_entry.first == "input_timelord_vdfs") {
			_entry.second.to(input_timelord_vdfs);
		} else if(_entry.first == "input_transactions") {
			_entry.second.to(input_transactions);
		} else if(_entry.first == "input_vdfs") {
			_entry.second.to(input_vdfs);
		} else if(_entry.first == "max_history") {
			_entry.second.to(max_history);
		} else if(_entry.first == "max_queue_ms") {
			_entry.second.to(max_queue_ms);
		} else if(_entry.first == "max_sync_jobs") {
			_entry.second.to(max_sync_jobs);
		} else if(_entry.first == "num_sync_retries") {
			_entry.second.to(num_sync_retries);
		} else if(_entry.first == "opencl_device") {
			_entry.second.to(opencl_device);
		} else if(_entry.first == "output_challenges") {
			_entry.second.to(output_challenges);
		} else if(_entry.first == "output_committed_blocks") {
			_entry.second.to(output_committed_blocks);
		} else if(_entry.first == "output_interval_request") {
			_entry.second.to(output_interval_request);
		} else if(_entry.first == "output_timelord_infuse") {
			_entry.second.to(output_timelord_infuse);
		} else if(_entry.first == "output_transactions") {
			_entry.second.to(output_transactions);
		} else if(_entry.first == "output_verified_blocks") {
			_entry.second.to(output_verified_blocks);
		} else if(_entry.first == "output_verified_vdfs") {
			_entry.second.to(output_verified_vdfs);
		} else if(_entry.first == "replay_height") {
			_entry.second.to(replay_height);
		} else if(_entry.first == "router_name") {
			_entry.second.to(router_name);
		} else if(_entry.first == "storage_path") {
			_entry.second.to(storage_path);
		} else if(_entry.first == "timelord_name") {
			_entry.second.to(timelord_name);
		} else if(_entry.first == "update_interval_ms") {
			_entry.second.to(update_interval_ms);
		}
	}
}

vnx::Variant NodeBase::get_field(const std::string& _name) const {
	if(_name == "input_vdfs") {
		return vnx::Variant(input_vdfs);
	}
	if(_name == "input_blocks") {
		return vnx::Variant(input_blocks);
	}
	if(_name == "input_transactions") {
		return vnx::Variant(input_transactions);
	}
	if(_name == "input_timelord_vdfs") {
		return vnx::Variant(input_timelord_vdfs);
	}
	if(_name == "input_harvester_proof") {
		return vnx::Variant(input_harvester_proof);
	}
	if(_name == "output_verified_vdfs") {
		return vnx::Variant(output_verified_vdfs);
	}
	if(_name == "output_verified_blocks") {
		return vnx::Variant(output_verified_blocks);
	}
	if(_name == "output_committed_blocks") {
		return vnx::Variant(output_committed_blocks);
	}
	if(_name == "output_transactions") {
		return vnx::Variant(output_transactions);
	}
	if(_name == "output_interval_request") {
		return vnx::Variant(output_interval_request);
	}
	if(_name == "output_timelord_infuse") {
		return vnx::Variant(output_timelord_infuse);
	}
	if(_name == "output_challenges") {
		return vnx::Variant(output_challenges);
	}
	if(_name == "max_queue_ms") {
		return vnx::Variant(max_queue_ms);
	}
	if(_name == "update_interval_ms") {
		return vnx::Variant(update_interval_ms);
	}
	if(_name == "max_history") {
		return vnx::Variant(max_history);
	}
	if(_name == "replay_height") {
		return vnx::Variant(replay_height);
	}
	if(_name == "max_sync_jobs") {
		return vnx::Variant(max_sync_jobs);
	}
	if(_name == "num_sync_retries") {
		return vnx::Variant(num_sync_retries);
	}
	if(_name == "opencl_device") {
		return vnx::Variant(opencl_device);
	}
	if(_name == "do_sync") {
		return vnx::Variant(do_sync);
	}
	if(_name == "storage_path") {
		return vnx::Variant(storage_path);
	}
	if(_name == "router_name") {
		return vnx::Variant(router_name);
	}
	if(_name == "timelord_name") {
		return vnx::Variant(timelord_name);
	}
	return vnx::Variant();
}

void NodeBase::set_field(const std::string& _name, const vnx::Variant& _value) {
	if(_name == "input_vdfs") {
		_value.to(input_vdfs);
	} else if(_name == "input_blocks") {
		_value.to(input_blocks);
	} else if(_name == "input_transactions") {
		_value.to(input_transactions);
	} else if(_name == "input_timelord_vdfs") {
		_value.to(input_timelord_vdfs);
	} else if(_name == "input_harvester_proof") {
		_value.to(input_harvester_proof);
	} else if(_name == "output_verified_vdfs") {
		_value.to(output_verified_vdfs);
	} else if(_name == "output_verified_blocks") {
		_value.to(output_verified_blocks);
	} else if(_name == "output_committed_blocks") {
		_value.to(output_committed_blocks);
	} else if(_name == "output_transactions") {
		_value.to(output_transactions);
	} else if(_name == "output_interval_request") {
		_value.to(output_interval_request);
	} else if(_name == "output_timelord_infuse") {
		_value.to(output_timelord_infuse);
	} else if(_name == "output_challenges") {
		_value.to(output_challenges);
	} else if(_name == "max_queue_ms") {
		_value.to(max_queue_ms);
	} else if(_name == "update_interval_ms") {
		_value.to(update_interval_ms);
	} else if(_name == "max_history") {
		_value.to(max_history);
	} else if(_name == "replay_height") {
		_value.to(replay_height);
	} else if(_name == "max_sync_jobs") {
		_value.to(max_sync_jobs);
	} else if(_name == "num_sync_retries") {
		_value.to(num_sync_retries);
	} else if(_name == "opencl_device") {
		_value.to(opencl_device);
	} else if(_name == "do_sync") {
		_value.to(do_sync);
	} else if(_name == "storage_path") {
		_value.to(storage_path);
	} else if(_name == "router_name") {
		_value.to(router_name);
	} else if(_name == "timelord_name") {
		_value.to(timelord_name);
	} else {
		throw std::logic_error("no such field: '" + _name + "'");
	}
}

/// \private
std::ostream& operator<<(std::ostream& _out, const NodeBase& _value) {
	_value.write(_out);
	return _out;
}

/// \private
std::istream& operator>>(std::istream& _in, NodeBase& _value) {
	_value.read(_in);
	return _in;
}

const vnx::TypeCode* NodeBase::static_get_type_code() {
	const vnx::TypeCode* type_code = vnx::get_type_code(VNX_TYPE_HASH);
	if(!type_code) {
		type_code = vnx::register_type_code(static_create_type_code());
	}
	return type_code;
}

std::shared_ptr<vnx::TypeCode> NodeBase::static_create_type_code() {
	auto type_code = std::make_shared<vnx::TypeCode>();
	type_code->name = "mmx.Node";
	type_code->type_hash = vnx::Hash64(0x289d7651582d76a3ull);
	type_code->code_hash = vnx::Hash64(0xc10445207d1d4e71ull);
	type_code->is_native = true;
	type_code->native_size = sizeof(::mmx::NodeBase);
	type_code->methods.resize(28);
	type_code->methods[0] = ::vnx::ModuleInterface_vnx_get_config_object::static_get_type_code();
	type_code->methods[1] = ::vnx::ModuleInterface_vnx_get_config::static_get_type_code();
	type_code->methods[2] = ::vnx::ModuleInterface_vnx_set_config_object::static_get_type_code();
	type_code->methods[3] = ::vnx::ModuleInterface_vnx_set_config::static_get_type_code();
	type_code->methods[4] = ::vnx::ModuleInterface_vnx_get_type_code::static_get_type_code();
	type_code->methods[5] = ::vnx::ModuleInterface_vnx_get_module_info::static_get_type_code();
	type_code->methods[6] = ::vnx::ModuleInterface_vnx_restart::static_get_type_code();
	type_code->methods[7] = ::vnx::ModuleInterface_vnx_stop::static_get_type_code();
	type_code->methods[8] = ::vnx::ModuleInterface_vnx_self_test::static_get_type_code();
	type_code->methods[9] = ::mmx::Node_get_height::static_get_type_code();
	type_code->methods[10] = ::mmx::Node_get_synced_height::static_get_type_code();
	type_code->methods[11] = ::mmx::Node_get_block::static_get_type_code();
	type_code->methods[12] = ::mmx::Node_get_block_at::static_get_type_code();
	type_code->methods[13] = ::mmx::Node_get_header_at::static_get_type_code();
	type_code->methods[14] = ::mmx::Node_get_block_hash::static_get_type_code();
	type_code->methods[15] = ::mmx::Node_get_txo_info::static_get_type_code();
	type_code->methods[16] = ::mmx::Node_get_tx_key::static_get_type_code();
	type_code->methods[17] = ::mmx::Node_add_block::static_get_type_code();
	type_code->methods[18] = ::mmx::Node_add_transaction::static_get_type_code();
	type_code->methods[19] = ::mmx::Node_get_transaction::static_get_type_code();
	type_code->methods[20] = ::mmx::Node_get_contract::static_get_type_code();
	type_code->methods[21] = ::mmx::Node_get_balance::static_get_type_code();
	type_code->methods[22] = ::mmx::Node_get_total_balance::static_get_type_code();
	type_code->methods[23] = ::mmx::Node_get_utxo_list::static_get_type_code();
	type_code->methods[24] = ::mmx::Node_get_stxo_list::static_get_type_code();
	type_code->methods[25] = ::mmx::Node_start_sync::static_get_type_code();
	type_code->methods[26] = ::vnx::addons::HttpComponent_http_request::static_get_type_code();
	type_code->methods[27] = ::vnx::addons::HttpComponent_http_request_chunk::static_get_type_code();
	type_code->fields.resize(23);
	{
		auto& field = type_code->fields[0];
		field.is_extended = true;
		field.name = "input_vdfs";
		field.value = vnx::to_string("network.vdfs");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[1];
		field.is_extended = true;
		field.name = "input_blocks";
		field.value = vnx::to_string("network.blocks");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[2];
		field.is_extended = true;
		field.name = "input_transactions";
		field.value = vnx::to_string("network.transactions");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[3];
		field.is_extended = true;
		field.name = "input_timelord_vdfs";
		field.value = vnx::to_string("timelord.proofs");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[4];
		field.is_extended = true;
		field.name = "input_harvester_proof";
		field.value = vnx::to_string("harvester.proofs");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[5];
		field.is_extended = true;
		field.name = "output_verified_vdfs";
		field.value = vnx::to_string("node.verified_vdfs");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[6];
		field.is_extended = true;
		field.name = "output_verified_blocks";
		field.value = vnx::to_string("node.verified_blocks");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[7];
		field.is_extended = true;
		field.name = "output_committed_blocks";
		field.value = vnx::to_string("node.committed_blocks");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[8];
		field.is_extended = true;
		field.name = "output_transactions";
		field.value = vnx::to_string("node.transactions");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[9];
		field.is_extended = true;
		field.name = "output_interval_request";
		field.value = vnx::to_string("timelord.requests");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[10];
		field.is_extended = true;
		field.name = "output_timelord_infuse";
		field.value = vnx::to_string("timelord.infuse");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[11];
		field.is_extended = true;
		field.name = "output_challenges";
		field.value = vnx::to_string("harvester.challenges");
		field.code = {12, 5};
	}
	{
		auto& field = type_code->fields[12];
		field.data_size = 4;
		field.name = "max_queue_ms";
		field.value = vnx::to_string(10000);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[13];
		field.data_size = 4;
		field.name = "update_interval_ms";
		field.value = vnx::to_string(1000);
		field.code = {7};
	}
	{
		auto& field = type_code->fields[14];
		field.data_size = 4;
		field.name = "max_history";
		field.value = vnx::to_string(1000);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[15];
		field.data_size = 4;
		field.name = "replay_height";
		field.value = vnx::to_string(-1);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[16];
		field.data_size = 4;
		field.name = "max_sync_jobs";
		field.value = vnx::to_string(64);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[17];
		field.data_size = 4;
		field.name = "num_sync_retries";
		field.value = vnx::to_string(3);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[18];
		field.data_size = 4;
		field.name = "opencl_device";
		field.value = vnx::to_string(0);
		field.code = {3};
	}
	{
		auto& field = type_code->fields[19];
		field.data_size = 1;
		field.name = "do_sync";
		field.value = vnx::to_string(true);
		field.code = {31};
	}
	{
		auto& field = type_code->fields[20];
		field.is_extended = true;
		field.name = "storage_path";
		field.code = {32};
	}
	{
		auto& field = type_code->fields[21];
		field.is_extended = true;
		field.name = "router_name";
		field.value = vnx::to_string("Router");
		field.code = {32};
	}
	{
		auto& field = type_code->fields[22];
		field.is_extended = true;
		field.name = "timelord_name";
		field.value = vnx::to_string("TimeLord");
		field.code = {32};
	}
	type_code->build();
	return type_code;
}

void NodeBase::vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) {
	const auto* _type_code = _value->get_type_code();
	while(_type_code) {
		switch(_type_code->type_hash) {
			case 0x94965d816d328467ull:
				handle(std::static_pointer_cast<const ::mmx::Block>(_value));
				return;
			case 0xa84a63942b8e5c6aull:
				handle(std::static_pointer_cast<const ::mmx::ProofOfTime>(_value));
				return;
			case 0x816e898b36befae0ull:
				handle(std::static_pointer_cast<const ::mmx::ProofResponse>(_value));
				return;
			case 0xce0462acdceaa5bcull:
				handle(std::static_pointer_cast<const ::mmx::Transaction>(_value));
				return;
			default:
				_type_code = _type_code->super;
		}
	}
	handle(std::static_pointer_cast<const vnx::Value>(_value));
}

std::shared_ptr<vnx::Value> NodeBase::vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) {
	switch(_method->get_type_hash()) {
		case 0x17f58f68bf83abc0ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_config_object>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_config_object_return::create();
			_return_value->_ret_0 = vnx_get_config_object();
			return _return_value;
		}
		case 0xbbc7f1a01044d294ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_config>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_config_return::create();
			_return_value->_ret_0 = vnx_get_config(_args->name);
			return _return_value;
		}
		case 0xca30f814f17f322full: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_set_config_object>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_set_config_object_return::create();
			vnx_set_config_object(_args->config);
			return _return_value;
		}
		case 0x362aac91373958b7ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_set_config>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_set_config_return::create();
			vnx_set_config(_args->name, _args->value);
			return _return_value;
		}
		case 0x305ec4d628960e5dull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_type_code>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_type_code_return::create();
			_return_value->_ret_0 = vnx_get_type_code();
			return _return_value;
		}
		case 0xf6d82bdf66d034a1ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_get_module_info>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_get_module_info_return::create();
			_return_value->_ret_0 = vnx_get_module_info();
			return _return_value;
		}
		case 0x9e95dc280cecca1bull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_restart>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_restart_return::create();
			vnx_restart();
			return _return_value;
		}
		case 0x7ab49ce3d1bfc0d2ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_stop>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_stop_return::create();
			vnx_stop();
			return _return_value;
		}
		case 0x6ce3775b41a42697ull: {
			auto _args = std::static_pointer_cast<const ::vnx::ModuleInterface_vnx_self_test>(_method);
			auto _return_value = ::vnx::ModuleInterface_vnx_self_test_return::create();
			_return_value->_ret_0 = vnx_self_test();
			return _return_value;
		}
		case 0x55f0d4ef7a117716ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_height>(_method);
			auto _return_value = ::mmx::Node_get_height_return::create();
			_return_value->_ret_0 = get_height();
			return _return_value;
		}
		case 0xc4fb44ec3d1a8bb7ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_synced_height>(_method);
			auto _return_value = ::mmx::Node_get_synced_height_return::create();
			_return_value->_ret_0 = get_synced_height();
			return _return_value;
		}
		case 0xeb3fabe56dec161aull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_block>(_method);
			auto _return_value = ::mmx::Node_get_block_return::create();
			_return_value->_ret_0 = get_block(_args->hash);
			return _return_value;
		}
		case 0xc69c9f876a00e48full: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_block_at>(_method);
			auto _return_value = ::mmx::Node_get_block_at_return::create();
			_return_value->_ret_0 = get_block_at(_args->height);
			return _return_value;
		}
		case 0x52658163d8767c79ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_header_at>(_method);
			auto _return_value = ::mmx::Node_get_header_at_return::create();
			_return_value->_ret_0 = get_header_at(_args->height);
			return _return_value;
		}
		case 0x43c5087066b73f38ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_block_hash>(_method);
			auto _return_value = ::mmx::Node_get_block_hash_return::create();
			_return_value->_ret_0 = get_block_hash(_args->height);
			return _return_value;
		}
		case 0xd9d0be3b95e67d52ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_txo_info>(_method);
			auto _return_value = ::mmx::Node_get_txo_info_return::create();
			_return_value->_ret_0 = get_txo_info(_args->key);
			return _return_value;
		}
		case 0xcbb3efe603251470ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_tx_key>(_method);
			auto _return_value = ::mmx::Node_get_tx_key_return::create();
			_return_value->_ret_0 = get_tx_key(_args->id);
			return _return_value;
		}
		case 0x63abca4d23f93894ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_add_block>(_method);
			auto _return_value = ::mmx::Node_add_block_return::create();
			add_block(_args->block);
			return _return_value;
		}
		case 0xd9782531c0e3f766ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_add_transaction>(_method);
			auto _return_value = ::mmx::Node_add_transaction_return::create();
			add_transaction(_args->tx);
			return _return_value;
		}
		case 0x9c76ca142292750full: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_transaction>(_method);
			auto _return_value = ::mmx::Node_get_transaction_return::create();
			_return_value->_ret_0 = get_transaction(_args->id);
			return _return_value;
		}
		case 0xa28704c65a67a293ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_contract>(_method);
			auto _return_value = ::mmx::Node_get_contract_return::create();
			_return_value->_ret_0 = get_contract(_args->address);
			return _return_value;
		}
		case 0x2e00172d0470479ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_balance>(_method);
			auto _return_value = ::mmx::Node_get_balance_return::create();
			_return_value->_ret_0 = get_balance(_args->address, _args->contract);
			return _return_value;
		}
		case 0x91e9019d224db4b0ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_total_balance>(_method);
			auto _return_value = ::mmx::Node_get_total_balance_return::create();
			_return_value->_ret_0 = get_total_balance(_args->addresses, _args->contract);
			return _return_value;
		}
		case 0x7f52e1aa01c66023ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_utxo_list>(_method);
			auto _return_value = ::mmx::Node_get_utxo_list_return::create();
			_return_value->_ret_0 = get_utxo_list(_args->addresses);
			return _return_value;
		}
		case 0xb4e1314236d07ca2ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_get_stxo_list>(_method);
			auto _return_value = ::mmx::Node_get_stxo_list_return::create();
			_return_value->_ret_0 = get_stxo_list(_args->addresses);
			return _return_value;
		}
		case 0x6c5be8aeb25ef3c8ull: {
			auto _args = std::static_pointer_cast<const ::mmx::Node_start_sync>(_method);
			auto _return_value = ::mmx::Node_start_sync_return::create();
			start_sync(_args->force);
			return _return_value;
		}
		case 0xe0b6c38f619bad92ull: {
			auto _args = std::static_pointer_cast<const ::vnx::addons::HttpComponent_http_request>(_method);
			http_request_async(_args->request, _args->sub_path, _request_id);
			return nullptr;
		}
		case 0x97e79d08440406d5ull: {
			auto _args = std::static_pointer_cast<const ::vnx::addons::HttpComponent_http_request_chunk>(_method);
			http_request_chunk_async(_args->request, _args->sub_path, _args->offset, _args->max_bytes, _request_id);
			return nullptr;
		}
	}
	auto _ex = vnx::NoSuchMethod::create();
	_ex->dst_mac = vnx_request ? vnx_request->dst_mac : vnx::Hash64();
	_ex->method = _method->get_type_name();
	return _ex;
}

void NodeBase::http_request_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::addons::HttpResponse>& _ret_0) const {
	auto _return_value = ::vnx::addons::HttpComponent_http_request_return::create();
	_return_value->_ret_0 = _ret_0;
	vnx_async_return(_request_id, _return_value);
}

void NodeBase::http_request_chunk_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::addons::HttpData>& _ret_0) const {
	auto _return_value = ::vnx::addons::HttpComponent_http_request_chunk_return::create();
	_return_value->_ret_0 = _ret_0;
	vnx_async_return(_request_id, _return_value);
}


} // namespace mmx


namespace vnx {

void read(TypeInput& in, ::mmx::NodeBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code) {
		switch(code[0]) {
			case CODE_OBJECT:
			case CODE_ALT_OBJECT: {
				Object tmp;
				vnx::read(in, tmp, type_code, code);
				value.from_object(tmp);
				return;
			}
			case CODE_DYNAMIC:
			case CODE_ALT_DYNAMIC:
				vnx::read_dynamic(in, value);
				return;
		}
	}
	if(!type_code) {
		vnx::skip(in, type_code, code);
		return;
	}
	if(code) {
		switch(code[0]) {
			case CODE_STRUCT: type_code = type_code->depends[code[1]]; break;
			case CODE_ALT_STRUCT: type_code = type_code->depends[vnx::flip_bytes(code[1])]; break;
			default: {
				vnx::skip(in, type_code, code);
				return;
			}
		}
	}
	const char* const _buf = in.read(type_code->total_field_size);
	if(type_code->is_matched) {
		if(const auto* const _field = type_code->field_map[12]) {
			vnx::read_value(_buf + _field->offset, value.max_queue_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[13]) {
			vnx::read_value(_buf + _field->offset, value.update_interval_ms, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[14]) {
			vnx::read_value(_buf + _field->offset, value.max_history, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[15]) {
			vnx::read_value(_buf + _field->offset, value.replay_height, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[16]) {
			vnx::read_value(_buf + _field->offset, value.max_sync_jobs, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[17]) {
			vnx::read_value(_buf + _field->offset, value.num_sync_retries, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[18]) {
			vnx::read_value(_buf + _field->offset, value.opencl_device, _field->code.data());
		}
		if(const auto* const _field = type_code->field_map[19]) {
			vnx::read_value(_buf + _field->offset, value.do_sync, _field->code.data());
		}
	}
	for(const auto* _field : type_code->ext_fields) {
		switch(_field->native_index) {
			case 0: vnx::read(in, value.input_vdfs, type_code, _field->code.data()); break;
			case 1: vnx::read(in, value.input_blocks, type_code, _field->code.data()); break;
			case 2: vnx::read(in, value.input_transactions, type_code, _field->code.data()); break;
			case 3: vnx::read(in, value.input_timelord_vdfs, type_code, _field->code.data()); break;
			case 4: vnx::read(in, value.input_harvester_proof, type_code, _field->code.data()); break;
			case 5: vnx::read(in, value.output_verified_vdfs, type_code, _field->code.data()); break;
			case 6: vnx::read(in, value.output_verified_blocks, type_code, _field->code.data()); break;
			case 7: vnx::read(in, value.output_committed_blocks, type_code, _field->code.data()); break;
			case 8: vnx::read(in, value.output_transactions, type_code, _field->code.data()); break;
			case 9: vnx::read(in, value.output_interval_request, type_code, _field->code.data()); break;
			case 10: vnx::read(in, value.output_timelord_infuse, type_code, _field->code.data()); break;
			case 11: vnx::read(in, value.output_challenges, type_code, _field->code.data()); break;
			case 20: vnx::read(in, value.storage_path, type_code, _field->code.data()); break;
			case 21: vnx::read(in, value.router_name, type_code, _field->code.data()); break;
			case 22: vnx::read(in, value.timelord_name, type_code, _field->code.data()); break;
			default: vnx::skip(in, type_code, _field->code.data());
		}
	}
}

void write(TypeOutput& out, const ::mmx::NodeBase& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] == CODE_OBJECT) {
		vnx::write(out, value.to_object(), nullptr, code);
		return;
	}
	if(!type_code || (code && code[0] == CODE_ANY)) {
		type_code = mmx::vnx_native_type_code_NodeBase;
		out.write_type_code(type_code);
		vnx::write_class_header<::mmx::NodeBase>(out);
	}
	else if(code && code[0] == CODE_STRUCT) {
		type_code = type_code->depends[code[1]];
	}
	char* const _buf = out.write(29);
	vnx::write_value(_buf + 0, value.max_queue_ms);
	vnx::write_value(_buf + 4, value.update_interval_ms);
	vnx::write_value(_buf + 8, value.max_history);
	vnx::write_value(_buf + 12, value.replay_height);
	vnx::write_value(_buf + 16, value.max_sync_jobs);
	vnx::write_value(_buf + 20, value.num_sync_retries);
	vnx::write_value(_buf + 24, value.opencl_device);
	vnx::write_value(_buf + 28, value.do_sync);
	vnx::write(out, value.input_vdfs, type_code, type_code->fields[0].code.data());
	vnx::write(out, value.input_blocks, type_code, type_code->fields[1].code.data());
	vnx::write(out, value.input_transactions, type_code, type_code->fields[2].code.data());
	vnx::write(out, value.input_timelord_vdfs, type_code, type_code->fields[3].code.data());
	vnx::write(out, value.input_harvester_proof, type_code, type_code->fields[4].code.data());
	vnx::write(out, value.output_verified_vdfs, type_code, type_code->fields[5].code.data());
	vnx::write(out, value.output_verified_blocks, type_code, type_code->fields[6].code.data());
	vnx::write(out, value.output_committed_blocks, type_code, type_code->fields[7].code.data());
	vnx::write(out, value.output_transactions, type_code, type_code->fields[8].code.data());
	vnx::write(out, value.output_interval_request, type_code, type_code->fields[9].code.data());
	vnx::write(out, value.output_timelord_infuse, type_code, type_code->fields[10].code.data());
	vnx::write(out, value.output_challenges, type_code, type_code->fields[11].code.data());
	vnx::write(out, value.storage_path, type_code, type_code->fields[20].code.data());
	vnx::write(out, value.router_name, type_code, type_code->fields[21].code.data());
	vnx::write(out, value.timelord_name, type_code, type_code->fields[22].code.data());
}

void read(std::istream& in, ::mmx::NodeBase& value) {
	value.read(in);
}

void write(std::ostream& out, const ::mmx::NodeBase& value) {
	value.write(out);
}

void accept(Visitor& visitor, const ::mmx::NodeBase& value) {
	value.accept(visitor);
}

} // vnx
