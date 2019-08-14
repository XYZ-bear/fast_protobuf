#pragma once
#include "setter.h"

#define Rigist(func_name,ID,proto_type,func_id)     \
public:                                                         \
	void func_name(proto_type &val);                            \
	void set_##func_id(){                                       \
		regist_callback<proto_type>(ID,&module_type::func_name);\
	}


class proto_module_bridge_base
{
public:
	virtual void impl_callback(uint32_t, const void*,size_t) = 0;
};

template<class T,class Proto>
class proto_module_bridge :public proto_module_bridge_base
{
public:
	T * mod;
	typedef void(T::*call_back)(Proto&);
	call_back func;
	Proto proto;
	void impl_callback(uint32_t id, const void* data,size_t size) {
		proto.unserialize_with_ids_((unsigned char*)data, size);
		(mod->*func)(proto);
	}
};

class proto_manager {
public:
	static proto_manager & get_instance() {
		static proto_manager mm;
		return mm;
	}
	void regist_proto_module_bridge(uint32_t id, proto_module_bridge_base* pmb) {
		if (id + 1 > protos.size())
			protos.resize(id + 1);
		protos[id] = pmb;
	}
	void impl(uint32_t id, const void* data,size_t size) {
		protos[id]->impl_callback(id, data, size);
	}
private:
	vector<proto_module_bridge_base*> protos;
};


template<class T>
class module{
private:
	static T mod;
protected:
	DEFINE_SETTER()
public:
	typedef T module_type;
	module() {
		get_instance();
		IMPL_SETTER(mod)
	}
	T & get_instance() {
		return mod;
	}
	template<class Proto>
	void regist_callback(uint32_t id, void(T::*func)(Proto&) ) {
		proto_module_bridge<T,Proto> *pmb = new proto_module_bridge<T, Proto>;
		pmb->mod = &mod;
		pmb->func = func;
		proto_manager::get_instance().regist_proto_module_bridge(id, pmb);
	};
};

template<class T>
T module<T>::mod;