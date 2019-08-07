#pragma once

#include <vector>
#include <map>
#include <string>
#include <stdarg.h>
#include <functional>
#include "varint.h"
using namespace std;

#define   MAX_VARINT32_BYTES   5
#define   MAX_UINT8            256
#define   MAX_UINT16           65536
#define   MAX_UINT24           16777216
#define   MAX_UINT32           4294967296

typedef char uid_t;

#define  PROPERTY_PRIVATE

#ifdef PROPERTY_PRIVATE
//NSM = number + string + message
#define NSM(TYPE,name,id,...) \
						private:\
							 TYPE name;\
							 void set_##id(){set_field<TYPE>(&name,id,__VA_ARGS__);}\
						public:\
							 void set_##name(TYPE name_v){ name=name_v;}\
							 TYPE &get_##name(){return name;}

#define VECTOR(TYPE,name,id,...) \
						private:\
							 vector<TYPE> name;\
							 void set_##id(){set_vector_field<TYPE>(id,&name);}\
						public:\
							 void add_##name(TYPE &val){name.push_back(val);}\
							 vector<TYPE> &get_##name(){return name;};\

#define MAP(KEY_TYPE,VAL_TYPE,name,id,...) \
						private:\
							 map<KEY_TYPE,VAL_TYPE> name;\
							 void set_##id(){set_map_field<KEY_TYPE,VAL_TYPE>(id,&name);}\
						public:\
							 void set_##name(map<KEY_TYPE,VAL_TYPE> &name_v){ name=name_v;}\
							 void add_##name(KEY_TYPE key,VAL_TYPE val){name[key]=val;}\
							 map<KEY_TYPE,VAL_TYPE> &get_##name(){return name;}\
							 VAL_TYPE &get_##name(KEY_TYPE key){return name[key];}
#else
#define RF(TYPE,name,id,...) \
						public:\
							 TYPE name;\
                        private:\
							 void set_##id(){set_field(&name,id,__VA_ARGS__);}\

#define VECTOR(TYPE,name,id,...) \
						public:\
							 vector<TYPE> name;\
                        private:\
							 void set_##id(){set_vector_field<TYPE>(id,&name);}\

#define MAP(KEY_TYPE,VAL_TYPE,name,id,...) \
						public:\
							 map<KEY_TYPE,VAL_TYPE> name;\
                        private:\
							 void set_##id(){set_map_field<KEY_TYPE,VAL_TYPE>(id,&name);}
#endif

#define disable false
#define required true

#define _____CLASS_BEGIN(class_name)\
class class_name:public proto_base{\
public:\
class_name(){DO_PRE_SET();}\
class_name(const class_name & c){*this=c;DO_PRE_SET();}\


#define _____CLASS_END };

//5bits
#define DEFINE_ALL_PRE_SET()\
virtual void set_1() {};virtual void set_2() {};virtual void set_3() {};virtual void set_4() {};\
virtual void set_5() {};virtual void set_6() {};virtual void set_7() {};virtual void set_8() {};\
virtual void set_9() {};virtual void set_10() {};virtual void set_11() {};virtual void set_12() {};\
virtual void set_13() {};virtual void set_14() {};virtual void set_15() {};virtual void set_16() {};\
virtual void set_17() {};virtual void set_18() {};virtual void set_19() {};virtual void set_20() {};\
virtual void set_21() {};virtual void set_22() {};virtual void set_23() {};virtual void set_24() {};\
virtual void set_25() {};virtual void set_26() {};virtual void set_27() {};virtual void set_28() {};\
virtual void set_29() {};virtual void set_30() {};virtual void set_31() {};virtual void set_32() {};\
virtual void set_33() {};virtual void set_34() {};virtual void set_35() {};virtual void set_36() {};\
virtual void set_37() {};virtual void set_38() {};virtual void set_39() {};virtual void set_40() {};\
virtual void set_41() {}; virtual void set_42() {}; virtual void set_43() {}; virtual void set_44() {};\
virtual void set_45() {}; virtual void set_46() {}; virtual void set_47() {}; virtual void set_48() {};\
virtual void set_49() {}; virtual void set_50() {}; virtual void set_51() {}; virtual void set_52() {};\
virtual void set_53() {}; virtual void set_54() {}; virtual void set_55() {}; virtual void set_56() {};\
virtual void set_57() {}; virtual void set_58() {}; virtual void set_59() {}; virtual void set_60() {};\
virtual void set_61() {}; virtual void set_62() {}; virtual void set_63() {}; virtual void set_64() {};\
virtual void set_65() {}; virtual void set_66() {}; virtual void set_67() {}; virtual void set_68() {};\
virtual void set_69() {}; virtual void set_70() {}; virtual void set_71() {}; virtual void set_72() {};\
virtual void set_73() {}; virtual void set_74() {}; virtual void set_75() {}; virtual void set_76() {};\
virtual void set_77() {}; virtual void set_78() {}; virtual void set_79() {}; virtual void set_80() {};\
virtual void set_81() {}; virtual void set_82() {}; virtual void set_83() {}; virtual void set_84() {};\
virtual void set_85() {}; virtual void set_86() {}; virtual void set_87() {}; virtual void set_88() {};\
virtual void set_89() {}; virtual void set_90() {}; virtual void set_91() {}; virtual void set_92() {};\

#define DO_PRE_SET() \
set_1();set_2();set_3();set_4();\
set_5();set_6();set_7();set_8();\
set_9();set_10();set_11();set_12();\
set_13();set_14();set_15();set_16();\
set_17();set_18();set_19();set_20();\
set_21();set_22();set_23();set_24();\
set_25();set_26();set_27();set_28();\
set_29();set_30();set_31();set_32();\
set_33();set_34();set_35();set_36();\
set_37();set_38();set_39();set_40();\
set_41();set_42();set_43();set_44();\
set_45();set_46();set_47();set_48();\
set_49();set_50();set_51();set_52();\
set_53();set_54();set_55();set_56();\
set_57();set_58();set_59();set_60();\
set_61();set_62();set_63();set_64();\
set_65();set_66();set_67();set_68();\
set_69();set_70();set_71();set_72();\
set_73();set_74();set_75();set_76();\
set_77();set_78();set_79();set_80();\
set_81();set_82();set_83();set_84();\
set_85();set_86();set_87();set_88();\
set_89();set_90();set_91();set_92();\


class proto_base
{
public:
	enum FieldType {
		TYPE_UINT32,
		TYPE_SINT32,
		TYPE_UINT64,
		TYPE_SINT64,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_STRING,
		TYPE_VECTOR,
		TYPE_MAP,
		TYPE_MESSAGE,
		TYPE_ERROR
	};

	typedef function<size_t(unsigned char *dest)> serialize_func_type;
	typedef function<size_t(const unsigned char *dest)> unserialize_func_type;
	typedef function<size_t()> size_func_type;

	struct field_info{
		serialize_func_type serialize;
		unserialize_func_type unserialize;
		size_func_type size;
	};
protected:
	serialize_func_type serialize_func_;
	unserialize_func_type unserialize_func_;
	size_func_type size_func_;

	template<class T1, class T2 = T1, class Container = T1>
	FieldType get_filed_type() {
		if (typeid(Container) == typeid(vector<T1>))
			return TYPE_VECTOR;
		else if (typeid(Container) == typeid(map<T1, T2>))
			return TYPE_MAP;
		else if (typeid(T1) == typeid(string))
			return TYPE_STRING;
		else if (is_base_of<proto_base, T1>())
			return TYPE_MESSAGE;
		else if (typeid(T1) == typeid(float))
			return TYPE_FLOAT;
		else if (typeid(T1) == typeid(double))
			return TYPE_DOUBLE;
		else if (is_unsigned<T1>() && sizeof(T1) <= 4)
			return TYPE_UINT32;
		else if (is_signed<T1>() && sizeof(T1) <= 4)
			return TYPE_SINT32;
		else if (is_unsigned<T1>() && sizeof(T1) == 8)
			return TYPE_UINT64;
		else if (is_signed<T1>() && sizeof(T1) == 8)
			return TYPE_SINT64;
		else
			return TYPE_ERROR;
	}

	template<class T>
	void set_serialize_callback(void *data, function<size_t(unsigned char *dest)> &serialize_func) {
		serialize_func = [data, this](unsigned char *dest)->size_t {
			unsigned char *next = dest;
			FieldType type = get_filed_type<T>();
			switch (type)
			{
			case TYPE_UINT32: {
				next += uint32_pack(*(uint32_t*)data, next);
			}break;
			case TYPE_SINT32: {
				next += uint32_pack(zigZag_encode32(*(int32_t*)data), next);
			}break;
			case TYPE_UINT64: {
				next += uint64_pack(*(uint64_t*)data, next);
			}break;
			case TYPE_SINT64: {
				next += uint64_pack(zigZag_encode64(*(int64_t*)data), next);
			}break;
			case TYPE_STRING: {
				string *str = reinterpret_cast<string *>(data);
				next += uint32_pack(str->size(), next);
				memcpy(next, str->c_str(), str->size());
				next += str->size();
			}break;
			case TYPE_FLOAT: {
				memcpy(next, data, 4);
				next += 4;
			}break;
			case TYPE_DOUBLE: {
				memcpy(next, data, 8);
				next += 8;
			}break;
			case TYPE_MESSAGE: {
				proto_base *pb = (proto_base*)(data);
				next += (pb->serialize_(next));
			}break;
			default:
				break;
			}
			return next - dest;
		};
	}

	template<class T>
	void set_unserialize_callback(void *data, function<size_t(const unsigned char *dest)> &unserialize_func) {
		unserialize_func = [data, this](const unsigned char *dest)->size_t {
			const unsigned char *next = dest;
			FieldType type = get_filed_type<T>();
			switch (type)
			{
			case TYPE_UINT32: {
				next += uint32_unpack(next, (uint32_t*)data);
			}break;
			case TYPE_SINT32: {
				uint32_t re;
				next += uint32_unpack(next, &re);
				//int32_t res = zigZag_decode32(re);
				int32_t *res = reinterpret_cast<int32_t *>(data);
				*res = zigZag_decode32(re);
				//*(T*)data = zigZag_decode32(re);
			}break;
			case TYPE_UINT64: {
				next += uint64_unpack(next, (uint64_t*)data);
			}break;
			case TYPE_SINT64: {
				uint64_t re;
				next += uint64_unpack(next, &re);
				int64_t *res = reinterpret_cast<int64_t *>(data);
				*res = zigZag_decode64(re);
				//*(T*)data = zigZag_decode64(re);
			}break;
			case TYPE_STRING: {
				uint32_t size;
				next += uint32_unpack(next, &size);
				string *str = reinterpret_cast<string *>(data);
				str->assign((char*)next, size);
				next += size;
			}break;
			case TYPE_FLOAT: {
				memcpy(data, next, 4);
				next += 4;
			}break;
			case TYPE_DOUBLE: {
				memcpy(data, next, 8);
				next += 8;
			}break;
			case TYPE_MESSAGE: {
				proto_base *pb = (proto_base*)(data);
				next += pb->unserialize_(next);
			}break;
			default:
				break;
			}
			return next - dest;
		};
	}

	template<class T>
	void set_size_callback(void *data, function<size_t()> &size_func) {
		size_func = [data, this]()->size_t {
			size_t size = 0;
			FieldType type = get_filed_type<T>();
			switch (type)
			{
			case TYPE_UINT32: {
				size += uint32_size(*(uint32_t*)data);
			}break;
			case TYPE_SINT32: {
				size += uint32_size(zigZag_encode32(*(int32_t*)data));
			}break;
			case TYPE_UINT64: {
				size += uint64_size(*(uint32_t*)data);
			}break;
			case TYPE_SINT64: {
				size += uint64_size(zigZag_encode64(*(int64_t*)data));
			}break;
			case TYPE_STRING: {
				string *str = reinterpret_cast<string *>(data);
				size += uint32_size(str->size());
				size += str->size();
			}break;
			case TYPE_FLOAT: {
				size += 4;
			}break;
			case TYPE_DOUBLE: {
				size += 8;
			}break;
			case TYPE_MESSAGE: {
				proto_base *pb = (proto_base*)(data);
				size += pb->get_size();
			}break;
			default:
				break;
			}
			return size;
		};
	}

	template<class T>
	void set_field(T *a, uid_t id, bool isrequird = false, bool enable = true) {
		auto &field = fields_[id];
		set_serialize_callback<T>(a, field.serialize);
		set_unserialize_callback<T>(a, field.unserialize); 
		set_size_callback<T>(a, field.size);
	}

	template< class T, class Contianer = vector<T>>
	void set_vector_field(uid_t id, Contianer *a, bool isrequird = false, bool enable = true) {
		auto &field = fields_[id];
		field.serialize = [a, this](unsigned char *dest)->size_t {
			unsigned char *next = dest;
			next += uint32_pack(a->size(), next);
			for (auto &ele : *a) {
				set_serialize_callback<T>(&ele, serialize_func_);
				next += serialize_func_(next);
			}
			return next - dest;
		};

		field.unserialize = [a, this](const unsigned char *dest)->size_t {
			const unsigned char *next = dest;
			size_t len;
			next += uint32_unpack(next, &len);
			a->resize(len);
			for (auto &ele : *a) {
				set_unserialize_callback<T>(&ele, unserialize_func_);
				next += unserialize_func_(next);
			}
			return next - dest;
		};

		field.size= [a, this]()->size_t {
			size_t size = 0;
			size += uint32_size(a->size());
			for (auto &ele : *a) {
				function<size_t()> func;
				set_size_callback<T>(&ele, size_func_);
				size += size_func_();
			}
			return size;
		};
	}

	template<class T1,class T2, class Contianer = map<T1,T2>>
	void set_map_field(uid_t id, Contianer *a, bool isrequird = false, bool enable = true) {
		auto &field = fields_[id];
		field.serialize = [a, this](unsigned char *dest)->size_t {
			unsigned char *next = dest;
			next += uint32_pack(a->size(), next);
			for (auto &ele : *a) {
				set_serialize_callback<T1>((T1*)&ele.first, serialize_func_);
				next += serialize_func_(next);

				set_serialize_callback<T2>(&ele.second, serialize_func_);
				next += serialize_func_(next);
			}
			return next - dest;
		};
		field.unserialize = [a, this](const unsigned char *dest)->size_t {
			const unsigned char *next = dest;
			size_t len;
			next += uint32_unpack(next, &len);
			for (size_t i = 0; i < len; i++) {
				T1 key;
				set_unserialize_callback<T1>(&key, unserialize_func_);
				next += unserialize_func_(next);

				T2 val;
				set_unserialize_callback<T2>(&val, unserialize_func_);
				next += unserialize_func_(next);

				a->insert(make_pair(key, val));
			}
			return next - dest;
		};

		field.size = [a, this]()->size_t {
			size_t size = 0;
			size += uint32_size(a->size());
			for (auto &ele : *a) {
				set_size_callback<T1>((T1*)&ele.first, size_func_);
				size += size_func_();

				set_size_callback<T2>(&ele.second, size_func_);
				size += size_func_();
			}
			return size;
		};
	}

	size_t unserialize_(const unsigned char *val) {
		const unsigned char*next = val;
		for (auto &field_i : fields_) {
			auto &field = field_i.second;
			next += field.unserialize(next);
		}
		return next - val;
	}

	size_t serialize_(unsigned char *dest) {
		unsigned char*next = dest;
		for (auto &field_i : fields_) {
			auto &field = field_i.second;
			next += field.serialize(next);
		}
		return next - dest;
	}

	map<char, field_info> fields_;
public:
	size_t unserialize(const unsigned char *val,size_t size) {
		if (size < get_size())
			return 0;
		return unserialize_(val);
	}

	size_t serialize(unsigned char *dest, size_t size) {
		if (size < get_size())
			return 0;
		return serialize_(dest);
	}

	size_t get_size() {
		size_t size = 0;
		for (auto &field_i : fields_) {
			auto &field = field_i.second;
			size += field.size();
		}
		return size;
	}

	//顶层值拷贝，meta信息保留，不进行拷贝
	void operator=(const proto_base &c) {
	}

protected:
	DEFINE_ALL_PRE_SET()
	~proto_base() {};
};