
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_contract_Symbol_HXX_
#define INCLUDE_mmx_contract_Symbol_HXX_

#include <mmx/contract/package.hxx>
#include <mmx/contract/NFT.hxx>


namespace mmx {
namespace contract {

class Symbol : public ::mmx::contract::NFT {
public:
	
	std::string text;
	
	typedef ::mmx::contract::NFT Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x52fce97e392e8710ull;
	
	Symbol() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<Symbol> create();
	std::shared_ptr<vnx::Value> clone() const override;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) override;
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const Symbol& _value);
	friend std::istream& operator>>(std::istream& _in, Symbol& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace mmx
} // namespace contract


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_contract_Symbol_HXX_
