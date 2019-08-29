#pragma once

#define OP_SERIALIZE 1
#define OP_UNSERIALIZE 2
#define OP_SIZE 3
#define OP_REFRESH 4
#define OP_DEFAULT 5
#define OP_COLLECTOR 6

#define _ ,

#ifdef ele
#undef ele
#endif

#ifdef ele_map
#undef ele_map
#endif

template<class VT, class RT = VT>
class operator_base
{
public:
	RT value;

	typedef VT value_type;
	operator_base() {}

	template<class T>
	void operator=(const T &v) {
		value = v;
	}

	template<class T>
	void operator=(T v) {
		value = v;
	}
	template<class T>
	operator const T &()const {
		return value;
	}
	template<class T>
	bool operator==(T v) {
		return value == v;
	}
	template<class T>
	bool operator!=(T v) {
		return value != v;
	}
};

class fixed32 :public operator_base<fixed32,uint32_t> {
public:
	template<class T>
	void operator=(T v) {
		value = v;
	}
	template<class T>
	fixed32(T v) {
		value = v;
	}
	fixed32() {}
};

class fixed64 :public operator_base<fixed64,uint64_t> {
public:
	template<class T>
	void operator=(T v) {
		value = v;
	}
	template<class T>
	fixed64(T v) {
		value = v;
	}
	fixed64() {}
};

template<class VT>
class enum_base :public operator_base<VT,int64_t>
{
public:
	template<class T>
	void operator=(const T v) {
		this->value = (VT)v;
	}
	template<class T>
	enum_base(T v) {
		this->value = (VT)v;
	}
	enum_base() {}
};