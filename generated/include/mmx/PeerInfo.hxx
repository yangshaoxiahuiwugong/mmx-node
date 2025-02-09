
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_PeerInfo_HXX_
#define INCLUDE_mmx_PeerInfo_HXX_

#include <mmx/package.hxx>
#include <mmx/peer_info_t.hxx>
#include <vnx/Value.h>


namespace mmx {

class PeerInfo : public ::vnx::Value {
public:
	
	std::vector<::mmx::peer_info_t> peers;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xf7a37f624c94a121ull;
	
	PeerInfo() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<PeerInfo> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const PeerInfo& _value);
	friend std::istream& operator>>(std::istream& _in, PeerInfo& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_PeerInfo_HXX_
