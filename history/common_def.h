#pragma once

#define OP_SERIALIZE 1
#define OP_UNSERIALIZE 2
#define OP_SIZE 3
#define OP_REFRESH 4
#define OP_DEFAULT 5
#define OP_COLLECTOR 6

//Къжиди
#define PRIVATE_ARGS_GLUE(x, y) x y
#define PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT(_1,_2,_3,_4,_5,_6,_7,_8,_9, N, ...) N
#define PRIVATE_MACRO_VAR_ARGS_IMPL(args)  PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT args
#define COUNT_MACRO_VAR_ARGS(...)  PRIVATE_MACRO_VAR_ARGS_IMPL((__VA_ARGS__,9,8,7,6,5,4,3,2,1,0))

#define PRIVATE_MACRO_CHOOSE_HELPER3(M,count)  M##count
#define PRIVATE_MACRO_CHOOSE_HELPER2(M,count) PRIVATE_MACRO_CHOOSE_HELPER3(M,count)
#define PRIVATE_MACRO_CHOOSE_HELPER1(M,count)  PRIVATE_MACRO_CHOOSE_HELPER2(M,count)
#define PRIVATE_MACRO_CHOOSE_HELPER(M,count)   PRIVATE_MACRO_CHOOSE_HELPER1(M,count)

#define INVOKE_VAR_MACRO(M,...) PRIVATE_ARGS_GLUE(PRIVATE_MACRO_CHOOSE_HELPER(M,COUNT_MACRO_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

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
		return (T&)value;
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
class enumm :public operator_base<VT,int64_t>
{
public:
	template<class T>
	void operator=(const T v) {
		this->value = (VT)v;
	}
	template<class T>
	enumm(T v) {
		this->value = (VT)v;
	}
	enumm() {}
};