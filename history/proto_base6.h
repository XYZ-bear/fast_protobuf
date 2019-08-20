#pragma once

#include <vector>
#include <map>
#include <string>
#include <stdarg.h>
#include <functional>
#include "varint.h"
using namespace std;

typedef char uid_t;

#define SIZE_1_BYTE 1
#define SIZE_2_BYTE 2
#define SIZE_4_BYTE 4
#define SIZE_8_BYTE 8

#define MODE_ID 1
#define MODE_TAG 2
#define MODE_NO 3

#define  PROPERTY_PRIVATE

#ifdef PROPERTY_PRIVATE
//NSM = number + string + message
#define NSM(TYPE,name,id,...) \
						private:\
							 proto_field<TYPE> pb_##id;\
							 TYPE name;\
						protected:\
							 size_t serialize_##id(){};
							 void set_##id(){set_field<TYPE>(&name,id,&pb_##id);}\
							 field_base* get_##id(){return &pb_##id;}\
						public:\
							 void set_##name(TYPE name_v){ name=name_v;}\
							 TYPE &get_##name(){return name;}

#define ENUM(TYPE,name,id,...) \
						private:\
							 proto_field<int64_t> pb_##id;\
							 TYPE name;\
							 void set_##id(){set_enum_field<TYPE>(&name,id);}\
                             field_base* get_##id(){return &pb_##id;}\
						public:\
							 void set_##name(TYPE val){ name=val;}\
							 TYPE &get_##name(){return name;}

#define FIXED(TYPE,name,id,...) \
						private:\
							 proto_field<TYPE::value_type, TYPE::value_type, TYPE> pb_##id;\
							 TYPE fixed_##name;\
							 TYPE::value_type name;\
							 void set_##id(){set_fixed_field<TYPE::value_type,TYPE>(id,&name,&fixed_##name,&pb_##id);}\
							 field_base* get_##id(){return &pb_##id;}\
						public:\
							 void set_##name(TYPE::value_type val){ name=val;}\
							 TYPE::value_type &get_##name(){return name;}

#define VECTOR(TYPE,name,id,...) \
						private:\
							 proto_field<TYPE, TYPE, vector<TYPE>> pb_##id;\
							 vector<TYPE> name;\
							 void set_##id(){set_vector_field<TYPE>(id,&name,&pb_##id);}\
							 field_base* get_##id(){return &pb_##id;}\
						public:\
							 void add_##name(TYPE &val){name.push_back(val);}\
							 vector<TYPE> &get_##name(){return name;};\

#define MAP(KEY_TYPE,VAL_TYPE,name,id,...) \
						private:\
							 proto_field<KEY_TYPE, VAL_TYPE, map<KEY_TYPE,VAL_TYPE>> pb_##id;\
							 map<KEY_TYPE,VAL_TYPE> name;\
							 void set_##id(){set_map_field<KEY_TYPE,VAL_TYPE>(id,&name);}\
							 field_base* get_##id(){return &pb_##id;}\
						public:\
							 void add_##name(KEY_TYPE key,VAL_TYPE val){name[key]=val;}\
							 map<KEY_TYPE,VAL_TYPE> &get_##name(){return name;}\
							 VAL_TYPE &get_##name(KEY_TYPE key){return name[key];}
#else
#define NSM(TYPE,name,id,...) \
						public:\
							 TYPE name;\
                        private:\
							 void set_##id(){set_field(&name,id,__VA_ARGS__);}\

#define ENUM(TYPE,name,id,...) \
						private:\
							 TYPE name;\
                        private:\
							 void set_##id(){set_enum_field<TYPE>(&name,id);}\

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

#define MESSAGE_BEGIN(class_name,...)\
class class_name:public proto_base{\
public:\
class_name(){DO_PRE_SET();}\
class_name(const class_name & c){*this=c;DO_PRE_SET();}\
static class_name &instance(){static class_name entity;entity.refresh();return entity;}

#define END };

#define OVERFLOW_CHECK(begin,end,size) if ((begin+size) > end) return 0;

#define CHECK_DEFAULT(data,default_value) if(data==default_value) return true;else return false;

#define BIT8(name) uint8_t name[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };

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
virtual void set_93() {}; virtual void set_94() {}; virtual void set_95() {}; virtual void set_96() {};\
virtual void set_97() {}; virtual void set_98() {}; virtual void set_99() {}; virtual void set_100() {};\

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
set_93();set_94();set_95();set_96();\
set_97();set_98();set_99();set_100();\

#define DEFINE_ALL_PRE_GET()\
virtual field_base* get_1(){return nullptr;};virtual field_base* get_2(){return nullptr;};virtual field_base* get_3(){return nullptr;};virtual field_base* get_4(){return nullptr;};\
virtual field_base* get_5(){return nullptr;};virtual field_base* get_6(){return nullptr;};virtual field_base* get_7(){return nullptr;};virtual field_base* get_8(){return nullptr;};\
virtual field_base* get_9(){return nullptr;};virtual field_base* get_10(){return nullptr;};virtual field_base* get_11(){return nullptr;};virtual field_base* get_12(){return nullptr;};\
virtual field_base* get_13(){return nullptr;};virtual field_base* get_14(){return nullptr;};virtual field_base* get_15(){return nullptr;};virtual field_base* get_16(){return nullptr;};

#define DEFINE_ALL_PRE_SERIALIZE()\
virtual size_t serialize_1(){return 0;};virtual size_t serialize_2(){return 0;};virtual size_t serialize_3(){return 0;};virtual size_t serialize_4(){return 0;};\
virtual size_t serialize_5(){return 0;};virtual size_t serialize_6(){return 0;};virtual size_t serialize_7(){return 0;};virtual size_t serialize_8(){return 0;};\
virtual size_t serialize_9(){return 0;};virtual size_t serialize_10(){return 0;};virtual size_t serialize_11(){return 0;};virtual size_t serialize_12(){return 0;};\
virtual size_t serialize_13(){return 0;};virtual size_t serialize_14(){return 0;};virtual size_t serialize_15(){return 0;};virtual size_t serialize_16(){return 0;};


#define IMPL_SERIALIZE()\
next+=serialize_1();next+=serialize_2();next+=serialize_3();next+=serialize_4();\
next+=serialize_5();next+=serialize_6();next+=serialize_7();next+=serialize_8();\
next+=serialize_9();next+=serialize_10();next+=serialize_11();next+=serialize_12();\
next+=serialize_13();next+=serialize_14();next+=serialize_15();next+=serialize_16();

enum WireType
{
	WireType_Varint = 0,
	WireType_Fix32 = 1,
	WireType_Fix64 = 2,
	WireType_Length_Limited = 3,
};

struct fixed32
{
	typedef uint32_t value_type;
	uint32_t *data;
	WireType type = WireType_Fix32;
};

struct fixed64
{
	typedef uint64_t value_type;
	uint64_t *data;
	WireType type = WireType_Fix64;
};

class proto_base;

class field_base {
public:
	virtual size_t serialize(unsigned char *begin, unsigned char *end) = 0;
	virtual size_t unserialize(const unsigned char *begin, const unsigned char *end) = 0;
	virtual size_t size() = 0;
	virtual bool   is_default() = 0;
	virtual void   refresh() = 0;
	WireType type;
};

template<class T1, class T2 = T1, class Container = T1>
class proto_field :public field_base {
public:
#pragma region serialize
	inline static size_t serialize_(bool *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_1_BYTE);
		memcpy(dest, data, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t serialize_(uint8_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_1_BYTE);
		memcpy(dest, data, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t serialize_(uint16_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(*(uint32_t*)data));
		return varint_pack(*(uint32_t*)data, dest);
	}
	inline static size_t serialize_(uint32_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(*data));
		return varint_pack(*data, dest);
	}
	inline static size_t serialize_(int8_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_1_BYTE);
		memcpy(dest, data, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t serialize_(int16_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(zigZag_encode(*(int32_t*)data)));
		return varint_pack(zigZag_encode(*(int32_t*)data), dest);
	}
	inline static size_t serialize_(int32_t *data, unsigned char *dest, unsigned char *end) {
		uint32_t zig = zigZag_encode(*data);
		OVERFLOW_CHECK(dest, end, varint_size(zig));
		return varint_pack(zig, dest);
	}
	inline static size_t serialize_(uint64_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(*data));
		return varint_pack(*data, dest);
	}
	inline static size_t serialize_(int64_t *data, unsigned char *dest, unsigned char *end) {
		uint64_t zig = zigZag_encode(*data);
		OVERFLOW_CHECK(dest, end, varint_size(zig));
		return varint_pack(zig, dest);
	}
	inline static size_t serialize_(string *data, unsigned char *dest, unsigned char *end) {
		unsigned char *next = dest;
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		next += varint_pack(size, next);
		if ((next + size) > end) return 0;
		memcpy(next, data->c_str(), size);
		return next - dest + size;
	}
	inline static size_t serialize_(double *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_8_BYTE);
		memcpy(dest, data, SIZE_8_BYTE);
		return SIZE_8_BYTE;
	}
	inline static size_t serialize_(float *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_4_BYTE);
		memcpy(dest, data, SIZE_4_BYTE);
		return SIZE_4_BYTE;
	}
	inline static size_t serialize_(fixed64 *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_8_BYTE);
		memcpy(dest, data->data, SIZE_8_BYTE);
		return SIZE_8_BYTE;
	}
	inline static size_t serialize_(fixed32 *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_4_BYTE);
		memcpy(dest, data->data, SIZE_4_BYTE);
		return SIZE_4_BYTE;
	}
	inline static size_t serialize_(proto_base *data, unsigned char *dest, unsigned char *end) {
		return data->serialize(dest, end - dest);
	}
	inline static size_t serialize_(vector<T1> *data, unsigned char *dest, unsigned char *end) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field<T1>::size_(&ele);
		}
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field<T1>::serialize_(&ele, next, end);
		}
		return next - dest;
	}
	inline static size_t serialize_(map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field<T1>::size_((T1*)&ele.first);
			size += proto_field<T2>::size_(&ele.second);
		}
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field<T1>::serialize_((T1*)&ele.first, next, end);
			next += proto_field<T2>::serialize_(&ele.second, next, end);
		}
		return next - dest;
	}
#pragma endregion

#pragma region unserialize
	inline static size_t unserialize_(bool *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_1_BYTE);
		memcpy(data, dest, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t unserialize_(uint8_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_1_BYTE);
		memcpy(data, dest, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t unserialize_(uint16_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		return varint_unpack(dest, (uint32_t*)data);
	}
	inline static size_t unserialize_(uint32_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		return varint_unpack(dest, data);
	}
	inline static size_t unserialize_(int8_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		memcpy(data, dest, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t unserialize_(int16_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		uint32_t re;
		size_t size = varint_unpack(next, &re);
		*res = zigZag_decode(re);
		return size;
	}
	inline static size_t unserialize_(int32_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		uint32_t re;
		size_t size = varint_unpack(dest, &re);
		*data = zigZag_decode(re);
		return size;
	}
	inline static size_t unserialize_(uint64_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		return varint_unpack(dest, data);
	}
	inline static size_t unserialize_(int64_t *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		uint64_t re;
		size_t size = varint_unpack(dest, &re);
		*data = zigZag_decode(re);
		return size;
	}
	inline static size_t unserialize_(string *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		uint32_t size;
		next += varint_unpack(next, &size);

		OVERFLOW_CHECK(next, end, size);
		data->assign((char*)next, size);
		return next - dest + size;
	}
	inline static size_t unserialize_(double *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_8_BYTE);
		memcpy(data, dest, SIZE_8_BYTE);

		return SIZE_8_BYTE;
	}
	inline static size_t unserialize_(float *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_4_BYTE);
		memcpy(data, dest, SIZE_4_BYTE);
		return SIZE_4_BYTE;
	}
	inline static size_t unserialize_(fixed64 *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_8_BYTE);
		memcpy(data->data, dest, SIZE_8_BYTE);

		return SIZE_8_BYTE;
	}
	inline static size_t unserialize_(fixed32 *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_4_BYTE);
		memcpy(data->data, dest, SIZE_4_BYTE);
		return SIZE_4_BYTE;
	}
	inline static size_t unserialize_(proto_base *data, const unsigned char *dest, const unsigned char *end) {
		return data->unserialize(dest, end - dest);
	}
	inline static size_t unserialize_(vector<T1> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		const unsigned char *last = next + len;
		data->resize(len);
		//data->reserve(len);
		size_t index = 0;
		while (next < last) {
			next += proto_field<T1>::unserialize_(&(*data)[index++], next, end);
		}
		data->reserve(index);
		return next - dest;
	}
	inline static size_t unserialize_(map<T1, T2> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		const unsigned char *last = next + len;
		T1 key;
		while (next < last) {
			next += proto_field<T1>::unserialize_(&key, next, end);

			T2 &val = (*data)[key];
			next += proto_field<T2>::unserialize_(&val, next, end);
		}
		return next - dest;
	}
#pragma endregion

#pragma region size
	inline static size_t size_(bool *data) {
		return SIZE_1_BYTE;
	}
	inline static size_t size_(uint8_t *data) {
		return SIZE_1_BYTE;
	}
	inline static size_t size_(uint16_t *data) {
		return varint_size(*(uint32_t*)data);
	}
	inline static size_t size_(uint32_t *data) {
		return varint_size(*data);
	}
	inline static size_t size_(int8_t *data) {
		return SIZE_1_BYTE;
	}
	inline static size_t size_(int16_t *data) {
		return varint_size(zigZag_encode(*(int32_t*)data));
	}
	inline static size_t size_(int32_t *data) {
		return varint_size(zigZag_encode(*data));
	}
	inline static size_t size_(uint64_t *data) {
		return varint_size(*data);
	}
	inline static size_t size_(int64_t *data) {
		return varint_size(zigZag_encode(*(int64_t*)data));
	}
	inline static size_t size_(string *data) {
		size_t size = 0;
		size += varint_size(data->size());
		size += data->size();
		return size;
	}
	inline static size_t size_(double *data) {
		return SIZE_8_BYTE;
	}
	inline static size_t size_(float *data) {
		return SIZE_4_BYTE;
	}
	inline static size_t size_(fixed64 *data) {
		return SIZE_8_BYTE;
	}
	inline static size_t size_(fixed32 *data) {
		return SIZE_4_BYTE;
	}
	inline static size_t size_(proto_base *data) {
		return data->size();
	}
	inline static size_t size_(vector<T1> *data) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field<T1>::size_(&ele);
		}
		size += varint_size(size);
		return size;
	}
	inline static size_t size_(map<T1, T2> *data) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field<T1>::size_((T1*)&ele.first);
			size += proto_field<T2>::size_(&ele.second);
		}
		size += varint_size(size);
		return size;
	}
#pragma endregion

#pragma region is_default
	inline static bool is_default_(bool *data) {
		CHECK_DEFAULT(*data, false);
	}
	inline static bool is_default_(uint8_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(uint16_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(uint32_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(int8_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(int16_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(int32_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(uint64_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(int64_t *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(string *data) {
		CHECK_DEFAULT(data->size(), 0);
	}
	inline static bool is_default_(double *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(float *data) {
		CHECK_DEFAULT(*data, 0);
	}
	inline static bool is_default_(fixed32 *data) {
		CHECK_DEFAULT(*(data->data), 0);
		return false;
	}
	inline static bool is_default_(fixed64 *data) {
		CHECK_DEFAULT(*(data->data), 0);
		return false;
	}
	inline static bool is_default_(proto_base *data) {
		CHECK_DEFAULT(data->size(), 0);
	}
	inline static bool is_default_(vector<T1> *data) {
		CHECK_DEFAULT(data->size(), 0);
	}
	inline static bool is_default_(map<T1, T2> *data) {
		CHECK_DEFAULT(data->size(), 0);
	}
#pragma endregion


#pragma region refresh
	inline static void refresh_(bool *data) {
		*data = false;
	}
	inline static void refresh_(uint8_t *data) {
		*data = 0;
	}
	inline static void refresh_(uint16_t *data) {
		*data = 0;
	}
	inline static void refresh_(uint32_t *data) {
		*data = 0;
	}
	inline static void refresh_(int8_t *data) {
		*data = 0;
	}
	inline static void refresh_(int16_t *data) {
		*data = 0;
	}
	inline static void refresh_(int32_t *data) {
		*data = 0;
	}
	inline static void refresh_(uint64_t *data) {
		*data = 0;
	}
	inline static void refresh_(int64_t *data) {
		*data = 0;
	}
	inline static void refresh_(string *data) {
		data->clear();
	}
	inline static void refresh_(double *data) {
		*data = 0;
	}
	inline static void refresh_(float *data) {
		*data = 0;
	}
	inline static void refresh_(fixed32 *data) {
		*(data->data) = 0;
	}
	inline static void refresh_(fixed64 *data) {
		*(data->data) = 0;
	}
	inline static void refresh_(proto_base *data) {
		data->refresh();
	}
	inline static void refresh_(vector<T1> *data) {
		data->clear();
	}
	inline static void refresh_(map<T1, T2> *data) {
		data->clear();
	}
#pragma endregion
public:
	size_t serialize(unsigned char *begin, unsigned char *end) {
		return serialize_(data_, begin, end);
	}
	size_t unserialize(const unsigned char *begin, const unsigned char *end) {
		return unserialize_(data_, begin, end);
	}
	size_t size() {
		return size_(data_);
	}
	bool is_default() {
		return is_default_(data_);
	}
	void set_data(Container *data) {
		data_ = data;
	}
	void refresh() {
		refresh_(data_);
	}
private:
	Container * data_;
};



class proto_base
{
public:
	~proto_base() {
		//for (auto field : proto_fields_) {
		//	delete field;
		//}
	}

	//顶层值拷贝，meta信息保留，不进行拷贝
	void operator=(const proto_base &c) {
	}

protected:
	template<class T1>
	static WireType get_nsm_type() {
		if (typeid(T1) == typeid(float))
			return WireType_Fix32;
		else if (typeid(T1) == typeid(double))
			return WireType_Fix64;
		else if (typeid(T1) == typeid(string))
			return WireType_Length_Limited;
		else
			return WireType_Varint;
	}

	template<class T,class F=proto_field<T>>
	void set_field(T *a, uid_t id, F *pb) {
		//proto_field<T> *pb2 = new proto_field<T>;
		pb->set_data(a);
		pb->type = get_nsm_type<T>();
		//proto_fields_.push_back(pb);
	}

	template<class T, class F = proto_field<T>>
	void set_enum_field(T *a, uid_t id,F *pb) {
		//if (sizeof(T) <= SIZE_4_BYTE) {
		//	proto_field<int32_t> *pb = new proto_field<int32_t>;
		//	pb->set_data((int32_t*)a);
		//	pb->type = WireType_Varint;
		//	proto_fields_.push_back(pb);
		//}
		//else {
		//	proto_field<int64_t> *pb = new proto_field<int64_t>;
		//	pb->set_data((int64_t*)a);
		//	pb->type = WireType_Varint;
		//	proto_fields_.push_back(pb);
		//}
			pb->set_data((int64_t*)a);
			pb->type = WireType_Varint;
			//proto_fields_.push_back(pb);
	}

	template< class T, class Contianer = vector<T>,class F= proto_field<T, T, Contianer>>
	void set_vector_field(uid_t id, Contianer *a, F *pb) {
		//proto_field<T, T, Contianer> *pb = new proto_field<T, T, Contianer>;
		pb->set_data(a);
		pb->type = WireType_Length_Limited;
		//proto_fields_.push_back(pb);
	}

	template<class T1, class T2, class Contianer = map<T1, T2>>
	void set_map_field(uid_t id, Contianer *a, bool isrequird = false, bool enable = true) {
		proto_field<T1, T2, Contianer> *pb = new proto_field<T1, T2, Contianer>;
		pb->set_data(a);
		pb->type = WireType_Length_Limited;
		//proto_fields_.push_back(pb);
	}

	template<class T, class Contianer,class F= proto_field<T, T, Contianer>>
	void set_fixed_field(uid_t id, T *a, Contianer *con, F *pb) {
		//proto_field<T, T, Contianer> *pb = new proto_field<T, T, Contianer>;
		con->data = a;
		pb->set_data(con);
		pb->type = con->type;
		///proto_fields_.push_back(pb);
	}

	DEFINE_ALL_PRE_SET()
	DEFINE_ALL_PRE_GET()
private:
#pragma region Mode_no

	size_t unserialize_(const unsigned char *val, size_t size) {
		const unsigned char*next = val;
		const unsigned char*end = val + size;
#ifdef _DEBUG
		for (auto &field : proto_fields_) {
			if (size_t t_size = field->unserialize(next, end))
				next += t_size;
			else
				return 0;
		}
#else
		for (auto iter = proto_fields_.begin(); iter != proto_fields_.end(); iter++)
		{
			if (size_t t_size = (*iter)->unserialize(next, end))
				next += t_size;
			else
				return 0;
		}
#endif // DEBUG
		return next - val;
	}

	size_t serialize_(unsigned char *dest, size_t size) {
		unsigned char*next = dest;
		unsigned char*end = dest + size;
#ifdef _DEBUG
		for (auto &field : proto_fields_) {
			next += field->serialize(next, end);
		}
#else
		for (auto iter = proto_fields_.begin(); iter != proto_fields_.end(); iter++) {
			if (size_t t_size = (*iter)->serialize(next, end))
				next += t_size;
			else
				return 0;
		}
#endif // DEBUG
		return next - dest;
	}

#pragma endregion

#pragma region Mode_id

	size_t serialize_with_ids_(unsigned char *next, size_t size) {
		size_t id_size = (proto_fields_.size() / SIZE_8_BYTE + 1);
		unsigned char *end = next + size;
		unsigned char *data_next = next + id_size;
		OVERFLOW_CHECK(next, end, id_size);
		BIT8(Bit_bit);
		memset(next, 0, id_size);
		size_t byte_index = 0, bit_index = 0;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			bit_index = i % SIZE_8_BYTE;
			if (!proto_fields_[i]->is_default()) {
				next[byte_index] |= Bit_bit[bit_index];
				if (size_t t_s = proto_fields_[i]->serialize(data_next, end))
					data_next += t_s;
				else
					return 0;
			}
			if (i != 0 && bit_index == 0) {
				byte_index++;
			}
		}
		return data_next - next;
	}

	size_t unserialize_with_ids_(const unsigned char *next, size_t size) {
		size_t id_size = (proto_fields_.size() / SIZE_8_BYTE + 1);
		const unsigned char *end = next + size;
		const unsigned char *data_next = next + id_size;
		OVERFLOW_CHECK(next, end, id_size);
		BIT8(Bit_bit);
		size_t byte_index = 0, bit_index = 0;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			bit_index = i % SIZE_8_BYTE;
			if (next[byte_index] & Bit_bit[bit_index]) {
				if (size_t t_s = proto_fields_[i]->unserialize(data_next, end))
					data_next += t_s;
				else
					return 0;
			}
			if (i != 0 && bit_index == 0)
				byte_index++;
		}
		return data_next - next;
	}

#pragma endregion

#pragma region Mode_tag
	size_t with_ids_size() {
		size_t size = (proto_fields_.size() / SIZE_8_BYTE + 1);
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			if (!proto_fields_[i]->is_default()) {
				size += proto_fields_[i]->size();
			}
		}
		return size;
	}

	size_t serialize_with_tag_(unsigned char *next, size_t size) {
		size_t tag_size = (proto_fields_.size() / 2 + 1);
		unsigned char *end = next + size;
		unsigned char *data_next = next + tag_size;

		OVERFLOW_CHECK(next, end, tag_size);
		memset(next, 0, tag_size);
		size_t byte_index = 0, tag_index = 0;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			tag_index = i % 2;
			auto &field = proto_fields_[i];
			if (i != 0 && tag_index == 0) {
				byte_index++;
			}
			uint8_t tag = next[byte_index];
			if (!field->is_default()) {
				tag = ((tag << 4) | field->type) | 0x08;
				next[byte_index] = tag;
				if (size_t t_s = proto_fields_[i]->serialize(data_next, end))
					data_next += t_s;
				else
					return 0;
			}

		}
		return data_next - next;
	}
	size_t unserialize_with_tag_(const unsigned char *next, size_t size) {
		size_t id_size = (proto_fields_.size() / 2 + 1);
		const unsigned char *end = next + size;
		const unsigned char *data_next = next + id_size;
		OVERFLOW_CHECK(next, end, id_size);
		size_t byte_index = 0, tag_index = 0;
		uint8_t tag = 0;
		WireType type;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			tag_index = i % 2;
			auto &field = proto_fields_[i];

			if (i != 0 && tag_index == 0) {
				byte_index++;
			}

			if (tag_index == 0)
				tag = next[byte_index];

			auto t_tag = tag >> 4;
			if (t_tag & 0x08) {
				type = (WireType)(t_tag ^ 0x08);
				if (field->type == type) {
					if (size_t t_s = field->unserialize(data_next, end))
						data_next += t_s;
					else
						return 0;
				}
				else {
					if (type == WireType_Varint) {
						data_next += varint_scan(data_next);
					}
					else if (type == WireType_Fix32) {
						data_next += SIZE_4_BYTE;
					}
					else if (type == WireType_Fix64) {
						data_next += SIZE_8_BYTE;
					}
					else {
						size_t len = 0;
						data_next += varint_unpack(data_next, &len);
						data_next += len;
					}
				}
			}
			tag = tag << 4;
		}
		return data_next - next;
	}

#pragma endregion
public:
	size_t serialize(unsigned char *next, size_t size, uint8_t mode = MODE_NO) {
		switch (mode)
		{
		case MODE_NO: {
			return serialize_(next, size);
		}break;
		case MODE_ID: {
			return serialize_with_ids_(next, size);
		}break;
		case MODE_TAG: {
			return serialize_with_tag_(next, size);
		}break;
		default:
			break;
		}
		return 0;
	}
	size_t unserialize(const unsigned char *next, size_t size, uint8_t mode = MODE_NO) {
		switch (mode)
		{
		case MODE_NO: {
			return unserialize_(next, size);
		}break;
		case MODE_ID: {
			return unserialize_with_ids_(next, size);
		}break;
		case MODE_TAG: {
			return unserialize_with_tag_(next, size);
		}break;
		default:
			break;
		}
		return 0;
	}

	void refresh() {
		for (auto &field : proto_fields_) {
			field->refresh();
		}
	}

	size_t size() {
		size_t size = 0;

#ifdef _DEBUG
		for (auto &field : proto_fields_) {
			size += field->size();
		}
#else
		for (auto iter = proto_fields_.begin(); iter != proto_fields_.end(); iter++) {
			size += (*iter)->size();
		}
#endif // DEBUG
		return size;
	}
private:
	vector<field_base*> proto_fields_;
};