#pragma once

#include <vector>
#include <map>
#include <string>
#include <stdarg.h>
#include <functional>
#include "varint.h"
#include "serializer.h"
using namespace std;

typedef char id_type;

#define SIZE_1_BYTE 1
#define SIZE_2_BYTE 2
#define SIZE_4_BYTE 4
#define SIZE_8_BYTE 8

#define MODE_ID 1
#define MODE_TAG 2
#define MODE_NO 3

#define  PROPERTY_PRIVATE

#ifdef PROPERTY_PRIVATE

#ifdef USE_TAG
#define OVERRIDE_OPERATER(ele,id,type,T1,T2)\
							public:\
							inline void operater_##id(uint8_t o){\
								switch (o)\
								{\
								case 1:{next+=serialize_tag_(next,id,type);next+=proto_field<T1,T2>::serialize_(&ele, next, end);}break;\
								case 2:{size_t uns=unserialize_tag_(unnext,id,type);if(uns==1) {unnext+=uns;unnext+=proto_field<T1,T2>::unserialize_(&ele, unnext, unend);}else unnext+=uns;}break;\
								case 3:{_size+=proto_field<T1,T2>::size_(&ele);}break;\
								case 4:{_size+=(proto_field<T1,T2>::size_(&ele)+1);}break;\
										default:break;\
								}\
							}
#else
#define OVERRIDE_OPERATER(ele,id,type,T1,T2)\
							public:\
							inline void operater_##id(uint8_t o){\
								switch (o)\
								{\
								case 1:{next+=proto_field<T1,T2>::serialize_(&ele, next, end);}break;\
								case 2:{unnext+=proto_field<T1,T2>::unserialize_(&ele, unnext, unend);}break;\
								case 3:{_size+=proto_field<T1,T2>::size_(&ele);}break;\
								case 4:{_size+=(proto_field<T1,T2>::size_(&ele)+1);}break;\
										default:break;\
								}\
							}
#endif // USE_TAG



#define NUMBER(TYPE,name,id,...) \
						private:\
							 TYPE name;\
							OVERRIDE_OPERATER(name,id,WireType_Varint,TYPE,TYPE);\
						public:\
							 void set_##name(TYPE name_v){ name=name_v;}\
							 TYPE &get_##name(){return name;}

#define STRING(TYPE,name,id,...) \
						private:\
							 TYPE name;\
							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited,TYPE,TYPE);\
						public:\
							 void set_##name(TYPE name_v){ name=name_v;}\
							 TYPE &get_##name(){return name;}


#define MSG(TYPE,name,id,...) \
						private:\
							 TYPE name;\
							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited,TYPE,TYPE);\
						public:\
							 void set_##name(TYPE name_v){ name=name_v;}\
							 TYPE &get_##name(){return name;}

#define ENUM(TYPE,name,id,...) \
						private:\
							 TYPE name;\
							 OVERRIDE_OPERATER(name,id,WireType_Varint,TYPE,TYPE);\
						public:\
							 void set_##name(TYPE val){ name=val;}\
							 TYPE &get_##name(){return name;}

#define FIXED(TYPE,name,id,...) \
						private:\
							 TYPE::value_type name;\
							 TYPE tt_##name{&name};\
							 OVERRIDE_OPERATER(tt_##name,id,WireType_Varint,TYPE,TYPE);\
						public:\
							 void set_##name(TYPE::value_type val){ name=val;}\
							 TYPE::value_type &get_##name(){return name;}

#define VECTOR(TYPE,name,id,...) \
						private:\
							 vector<TYPE> name;\
							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited,TYPE,TYPE);\
						public:\
							 void add_##name(TYPE &val){name.push_back(val);}\
							 vector<TYPE> &get_##name(){return name;};\

#define MAP(KEY_TYPE,VAL_TYPE,name,id,...) \
						private:\
							 map<KEY_TYPE,VAL_TYPE> name;\
							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited,KEY_TYPE,VAL_TYPE);\
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

#define MESSAGE(class_name)\
	class class_name:public proto_base\

#define MESSAGE_(class_name,parent)\
	class class_name:public parent\

#define OVERFLOW_CHECK(begin,end,size) if ((begin+size) > end) return 0;

#define CHECK_DEFAULT(data,default_value) if(data==default_value) return true;else return false;

#define BIT8(name) uint8_t name[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };

#define SERIALISE(entity,data,size) entity.serialize(&entity,data, size)

#define UNSERIALISE(entity,data,size) entity.unserialize(&entity,data, size)


//#define DEFINE_ALL_OPERATER()\
//inline void operater_1(uint8_t o){};inline void operater_2(uint8_t o){};inline void operater_3(uint8_t o){};inline void operater_4(uint8_t o){};inline void operater_5(uint8_t o){};inline void operater_6(uint8_t o){};\
//inline void operater_7(uint8_t o){};inline void operater_8(uint8_t o){};inline void operater_9(uint8_t o){};inline void operater_10(uint8_t o){};inline void operater_11(uint8_t o){};inline void operater_12(uint8_t o){};\
//inline void operater_13(uint8_t o){};inline void operater_14(uint8_t o){};inline void operater_15(uint8_t o){};inline void operater_16(uint8_t o){};
//
//#define IMPL_OPERATER(entity, o)\
//entity->operater_1(o); entity->operater_2(o); entity->operater_3(o); entity->operater_4(o); entity->operater_5(o); entity->operater_6(o); \
//entity->operater_7(o); entity->operater_8(o); entity->operater_9(o); entity->operater_10(o); entity->operater_11(o); entity->operater_12(o); \
//entity->operater_13(o); entity->operater_14(o); entity->operater_15(o); entity->operater_16(o);

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
	static WireType type;// = WireType_Fix32;
};
WireType fixed32::type = WireType_Fix32;

struct fixed64
{
	typedef uint64_t value_type;
	uint64_t *data;
	static WireType type;// = WireType_Fix64;
};
WireType fixed64::type = WireType_Fix32;

//template<class T>
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

template<class T1, class T2 = T1>
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
#ifdef USE_TAG
	inline static size_t serialize_(proto_base *data, unsigned char *dest, unsigned char *end) {
		T1 *entity = (T1*)data;
		size_t size = entity->size_with_tag(entity);
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		next += entity->serialize(entity, next, end - next);
		return next - dest;
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
#else
	inline static size_t serialize_(proto_base *data, unsigned char *dest, unsigned char *end) {
		T1 *entity = (T1*)data;
		return entity->serialize(entity, dest, end - dest);
	}
	inline static size_t serialize_(vector<T1> *data, unsigned char *dest, unsigned char *end) {
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field<T1>::serialize_(&ele, next, end);
		}
		return next - dest;
	}
	inline static size_t serialize_(map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field<T1>::serialize_((T1*)&ele.first, next, end);
			next += proto_field<T2>::serialize_(&ele.second, next, end);
		}
		return next - dest;
	}
#endif // USE_TAG


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
		*data = zigZag_decode(re);
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
#ifdef USE_TAG
	inline static size_t unserialize_(proto_base *data, const unsigned char *dest, const unsigned char *end) {
		T1 *entity = (T1*)data;
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		next += entity->unserialize(entity, next, end - next);
		return next - dest;
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
		data->resize(index);
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
#else
	inline static size_t unserialize_(proto_base *data, const unsigned char *dest, const unsigned char *end) {
		T1 *entity = (T1*)data;
		return entity->unserialize(entity, dest, end - dest);
	}
	inline static size_t unserialize_(vector<T1> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		data->resize(len);
		for (auto &ele : *data) {
			next += proto_field<T1>::unserialize_(&ele, next, end);
		}
		return next - dest;
	}
	inline static size_t unserialize_(map<T1, T2> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		T1 key;
		for (int i = 0; i < len; i++) {
			next += proto_field<T1>::unserialize_(&key, next, end);

			T2 &val = (*data)[key];
			next += proto_field<T2>::unserialize_(&val, next, end);
		}
		return next - dest;
	}
#endif // USE_TAG

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
		T1 *entity = (T1*)data;
		return entity->size(entity);
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
};


//template<class T>
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
	DEFINE_ALL_OPERATER()

	size_t serialize_tag_(unsigned char *nex,id_type id,WireType type) {
		id_type key = (id << 2) | (id_type)type;
		memcpy(nex, &key, sizeof(id_type));
		return 1;
	}

	size_t unserialize_tag_(const unsigned char *nex, id_type id, WireType type) {
		id_type key = nex[0];
		id_type iid = key >> 2;
		id_type kTagTypeMask = (1 << 2) - 1;
		WireType ttype = WireType(key & kTagTypeMask);
		if (iid == id && type == ttype) {
			return 1;
		}
		else {
			nex++;
			if (ttype == WireType_Varint) {
				return varint_scan(nex) + 1;
			}
			else if (ttype == WireType_Fix32) {
				return SIZE_4_BYTE + 1;
			}
			else if (ttype == WireType_Fix64) {
				return SIZE_8_BYTE + 1;
			}
			else {
				size_t len = 0;
				size_t size = 0;
				size += varint_unpack(nex, &len);
				size += len;
				return size + 1;
			}
		}
	}
public:
	template<class T>
	size_t serialize(T *entity,unsigned char *nex, size_t size) {
		next = nex; end = next + size;
		IMPL_OPERATER(entity, 1);
		return next - nex;
	}
	template<class T>
	size_t unserialize(T *entity,const unsigned char *nex, size_t size) {
		unnext = nex;
		unend = unnext + size;
		IMPL_OPERATER(entity, 2);
		return unnext - nex;
	}
	template<class T>
	size_t size(T *entity) {
		_size = 0;
		IMPL_OPERATER(entity, 3);
		return _size;
	}
	template<class T>
	size_t size_with_tag(T *entity) {
		_size = 0;
		IMPL_OPERATER(entity, 4);
		return _size;
	}
	template<class T>
	static T &instance() {
		static T entity;
		return entity;
	}
	void refresh() {}
protected:
	unsigned char *next;
	unsigned char *end;
	const unsigned char *unnext;
	const unsigned char *unend;
	size_t _size;
};