
// AUTO GENERATED by vnxcppcodegen

#include <mmx/contract/Condition.hxx>
#include <mmx/contract/Locked.hxx>
#include <mmx/contract/MultiSig.hxx>
#include <mmx/contract/NFT.hxx>
#include <mmx/contract/Nobody.hxx>
#include <mmx/contract/PubKey.hxx>
#include <mmx/contract/Staking.hxx>
#include <mmx/contract/Symbol.hxx>
#include <mmx/contract/Token.hxx>
#include <mmx/contract/compare_e.hxx>
#include <mmx/contract/condition_e.hxx>

#include <mmx/contract/package.hxx>
#include <vnx/vnx.h>



namespace vnx {

void type<::mmx::contract::Condition>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::Condition());
}

void type<::mmx::contract::Condition>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::Condition& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::Locked>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::Locked());
}

void type<::mmx::contract::Locked>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::Locked& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::MultiSig>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::MultiSig());
}

void type<::mmx::contract::MultiSig>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::MultiSig& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::NFT>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::NFT());
}

void type<::mmx::contract::NFT>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::NFT& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::Nobody>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::Nobody());
}

void type<::mmx::contract::Nobody>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::Nobody& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::PubKey>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::PubKey());
}

void type<::mmx::contract::PubKey>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::PubKey& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::Staking>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::Staking());
}

void type<::mmx::contract::Staking>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::Staking& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::Symbol>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::Symbol());
}

void type<::mmx::contract::Symbol>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::Symbol& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::Token>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::Token());
}

void type<::mmx::contract::Token>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::Token& value, bool special) {
	code.push_back(CODE_OBJECT);
}

void type<::mmx::contract::compare_e>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::compare_e());
}

void type<::mmx::contract::compare_e>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::compare_e& value, bool special) {
	if(!special || value.is_valid()) {
		code.push_back(CODE_STRING);
	} else {
		code.push_back(CODE_UINT32);
	}
}

void type<::mmx::contract::condition_e>::create_dynamic_code(std::vector<uint16_t>& code) {
	create_dynamic_code(code, ::mmx::contract::condition_e());
}

void type<::mmx::contract::condition_e>::create_dynamic_code(std::vector<uint16_t>& code, const ::mmx::contract::condition_e& value, bool special) {
	if(!special || value.is_valid()) {
		code.push_back(CODE_STRING);
	} else {
		code.push_back(CODE_UINT32);
	}
}


} // namespace vnx


namespace mmx {
namespace contract {


static void register_all_types() {
	vnx::register_type_code(::mmx::contract::Condition::static_create_type_code());
	vnx::register_type_code(::mmx::contract::Locked::static_create_type_code());
	vnx::register_type_code(::mmx::contract::MultiSig::static_create_type_code());
	vnx::register_type_code(::mmx::contract::NFT::static_create_type_code());
	vnx::register_type_code(::mmx::contract::Nobody::static_create_type_code());
	vnx::register_type_code(::mmx::contract::PubKey::static_create_type_code());
	vnx::register_type_code(::mmx::contract::Staking::static_create_type_code());
	vnx::register_type_code(::mmx::contract::Symbol::static_create_type_code());
	vnx::register_type_code(::mmx::contract::Token::static_create_type_code());
	vnx::register_type_code(::mmx::contract::compare_e::static_create_type_code());
	vnx::register_type_code(::mmx::contract::condition_e::static_create_type_code());
}

static struct vnx_static_init {
	vnx_static_init() {
		register_all_types();
	}
} vnx_static_init_;

const vnx::TypeCode* const vnx_native_type_code_Condition = vnx::get_type_code(vnx::Hash64(0x85f70b1c8de5f940ull));
const vnx::TypeCode* const vnx_native_type_code_Locked = vnx::get_type_code(vnx::Hash64(0xd0ff1b6e7bad1493ull));
const vnx::TypeCode* const vnx_native_type_code_MultiSig = vnx::get_type_code(vnx::Hash64(0x7d674c5f7297dedull));
const vnx::TypeCode* const vnx_native_type_code_NFT = vnx::get_type_code(vnx::Hash64(0x7cb24b9888a47906ull));
const vnx::TypeCode* const vnx_native_type_code_Nobody = vnx::get_type_code(vnx::Hash64(0xe41a6e3df6d9e791ull));
const vnx::TypeCode* const vnx_native_type_code_PubKey = vnx::get_type_code(vnx::Hash64(0x9b3cd508d7f41423ull));
const vnx::TypeCode* const vnx_native_type_code_Staking = vnx::get_type_code(vnx::Hash64(0xf058a3326fc2e7dcull));
const vnx::TypeCode* const vnx_native_type_code_Symbol = vnx::get_type_code(vnx::Hash64(0x52fce97e392e8710ull));
const vnx::TypeCode* const vnx_native_type_code_Token = vnx::get_type_code(vnx::Hash64(0x2d8835d6429431b2ull));
const vnx::TypeCode* const vnx_native_type_code_compare_e = vnx::get_type_code(vnx::Hash64(0xe27ffb2535efa133ull));
const vnx::TypeCode* const vnx_native_type_code_condition_e = vnx::get_type_code(vnx::Hash64(0xd11073d2e6a56dd6ull));

} // namespace mmx
} // namespace contract
