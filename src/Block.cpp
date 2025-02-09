/*
 * Block.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: mad
 */

#include <mmx/Block.hxx>
#include <mmx/write_bytes.h>


namespace mmx {

void Block::finalize()
{
	tx_hash = calc_tx_hash();
	hash = calc_hash();
}

vnx::bool_t Block::is_valid() const
{
	return BlockHeader::is_valid() && calc_tx_hash() == tx_hash;
}

mmx::hash_t Block::calc_tx_hash() const
{
	std::vector<uint8_t> buffer;
	vnx::VectorOutputStream stream(&buffer);
	vnx::OutputBuffer out(&stream);

	buffer.reserve(1024 * 1024);

	for(const auto& tx : tx_list) {
		write_bytes(out, tx->calc_hash());
	}
	out.flush();

	return hash_t(buffer);
}

std::shared_ptr<const BlockHeader> Block::get_header() const
{
	auto header = BlockHeader::create();
	header->operator=(*this);
	return header;
}


} // mmx
