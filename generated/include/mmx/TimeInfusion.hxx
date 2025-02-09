
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_mmx_TimeInfusion_HXX_
#define INCLUDE_mmx_TimeInfusion_HXX_

#include <mmx/package.hxx>
#include <mmx/hash_t.hpp>
#include <vnx/Value.h>


namespace mmx {

class TimeInfusion : public ::vnx::Value {
public:
	
	uint32_t chain = 0;
	std::map<uint64_t, ::mmx::hash_t> values;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x7c38bc7150b0d98bull;
	
	TimeInfusion() {}
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<TimeInfusion> create();
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
	
	friend std::ostream& operator<<(std::ostream& _out, const TimeInfusion& _value);
	friend std::istream& operator>>(std::istream& _in, TimeInfusion& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace mmx


namespace vnx {

} // vnx

#endif // INCLUDE_mmx_TimeInfusion_HXX_
