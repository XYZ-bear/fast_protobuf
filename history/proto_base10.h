#pragma once

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <set>
#include "varint2.h"
#include "option.h"
#include "serializer.h"
#include "common_def.h"
#include "collector.h"
using namespace std;

typedef uint32_t id_type;

#ifdef ele
#undef ele
#endif

#ifdef ele_map
#undef ele_map
#endif

#ifdef ele_enum
#undef ele_enum
#endif

#ifdef ele_unordered_map
#undef ele_unordered_map
#endif

#ifdef MESSAGE
#undef MESSAGE
#endif

#ifdef UNION_TYPE3
#undef UNION_TYPE3
#endif

#ifdef UNION_TYPE4
#undef UNION_TYPE4
#endif

#define SIZE_1_BYTE 1
#define SIZE_2_BYTE 2
#define SIZE_4_BYTE 4
#define SIZE_8_BYTE 8

#define WIRE_TYPE_LEN 2

#ifdef USE_TAG
#define OVERRIDE_OPERATER(ele,id,type)\
							public:\
							inline void operater_##id(uint8_t o){\
								switch (o)\
								{\
								case OP_SERIALIZE:{\
									if (!proto_field::is_default_(&ele)) {\
										serialize_tag_(id, type);\
										next += proto_field::serialize_(&ele, next, end);\
									}\
								}break;\
								case OP_UNSERIALIZE:{\
									if(unserialize_tag_(id,type))\
										unnext+=proto_field::unserialize_(&ele, unnext, unend);\
								}break;\
								case OP_SIZE:{_size+=(proto_field::size_(&ele)+size_tag_(id,type));}break;\
								case OP_REFRESH:{proto_field::refresh_(&ele);}break;\
								case OP_DEFAULT:{if(!proto_field::is_default_(&ele)){_is_default=false;return;}}break;\
										default:break;\
								}\
							}
#else
#define OVERRIDE_OPERATER(ele,id,type)\
							public:\
							inline void operater_##id(uint8_t o){\
								switch (o)\
								{\
								case OP_SERIALIZE:{next+=proto_field::serialize_(&ele, next, end);}break;\
								case OP_UNSERIALIZE:{unnext+=proto_field::unserialize_(&ele, unnext, unend);}break;\
								case OP_SIZE:{_size+=proto_field::size_(&ele);}break;\
								case OP_REFRESH:{proto_field::refresh_(&ele);}break;\
								case OP_DEFAULT:{if(!proto_field::is_default_(&ele)){_is_default=false;return;}}break;\
										default:break;\
								}\
							}
#endif // USE_TAG

#ifdef USE_SET_GET

#define ele(TYPE,name,id) \
						private:\
							 TYPE name;\
							 OVERRIDE_OPERATER(name,id,WireType_Varint);\
						public:\
							 void set_##name(TYPE name_v){ name=name_v;}\
							 TYPE get_##name(){return name;}

#define ele_enum(TYPE,name,id) \
						private:\
							 enumm<TYPE> name;\
							 OVERRIDE_OPERATER(name,id,WireType_Varint);\
						public:\
							 void set_##name(TYPE val){ name=val;}\
							 TYPE get_##name(){return name;}


#define ele_map(KEY_TYPE,VAL_TYPE,name,id,...) \
						private:\
							 map<KEY_TYPE,VAL_TYPE> name;\
							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
						public:\
							 void add_##name(KEY_TYPE key,VAL_TYPE val){name[key]=val;}\
							 map<KEY_TYPE,VAL_TYPE> &get_##name(){return name;}\
							 VAL_TYPE &get_##name(KEY_TYPE key){return name[key];}

#define ele_unordered_map(KEY_TYPE,VAL_TYPE,name,id,...) \
						private:\
							 unordered_map<KEY_TYPE,VAL_TYPE> name;\
							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
						public:\
							 void add_##name(KEY_TYPE key,VAL_TYPE val){name[key]=val;}\
							 unordered_map<KEY_TYPE,VAL_TYPE> &get_##name(){return name;}\
							 VAL_TYPE &get_##name(KEY_TYPE key){return name[key];}

#else

#define UNION_TYPE3(t1, name, id) \
public:\
	t1 name;\
	OVERRIDE_OPERATER(name,id,proto_field::type_(&name));


#define UNION_TYPE4(t1, t2, name, id) \
public:\
	t1,##t2 name;\
	OVERRIDE_OPERATER(name,id,proto_field::type_(&name));

#define ele(...) INVOKE_VAR_MACRO(UNION_TYPE, __VA_ARGS__)

#endif

#define MESSAGE(class_name)\
	class class_name:public proto_base<class_name>\

#define OVERFLOW_CHECK(begin,end,size) if ((begin+size) > end) return 0;

#define CHECK_DEFAULT(data,default_value) if(data==default_value) return true;else return false;

#define SERIALISE(entity,data,size) entity.serialize(&entity,data, size)

#define UNSERIALISE(entity,data,size) entity.unserialize(&entity,data, size)

enum WireType
{
	WireType_Varint = 0,
	WireType_Fix32 = 1,
	WireType_Fix64 = 2,
	WireType_Length_Limited = 3,
};

template<class T>
class proto_base;

class proto_field {
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
		memcpy(dest, data, SIZE_8_BYTE);
		return SIZE_8_BYTE;
	}

	inline static size_t serialize_(fixed32 *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_4_BYTE);
		memcpy(dest, data, SIZE_4_BYTE);
		return SIZE_4_BYTE;
	}

	template<class T>
	inline static size_t serialize_(enumm<T> *data, unsigned char *dest, unsigned char *end) {
		return serialize_(&(data->value), dest, end);
	}

#ifdef USE_TAG
	template<class T1>
	inline static size_t serialize_(proto_base<T1> *data, unsigned char *dest, unsigned char *end) {
		T1 *entity = (T1*)data;
		size_t size = entity->size(entity);
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		next += entity->serialize(entity, next, end - next);
		return next - dest;
	}

	template<class T1>
	inline static size_t serialize_(vector<T1> *data, unsigned char *dest, unsigned char *end) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_(&ele);
		}
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_(&ele, next, end);
		}
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t serialize_(map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_((T1*)&ele.first);
			size += proto_field::size_(&ele.second);
		}
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_((T1*)&ele.first, next, end);
			next += proto_field::serialize_(&ele.second, next, end);
		}
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t serialize_(unordered_map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_((T1*)&ele.first);
			size += proto_field::size_(&ele.second);
		}
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_((T1*)&ele.first, next, end);
			next += proto_field::serialize_(&ele.second, next, end);
		}
		return next - dest;
	}

	template<class T1>
	inline static size_t serialize_(set<T1> *data, unsigned char *dest, unsigned char *end) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_((T1*)&ele);
		}
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_((T1*)&ele, next, end);
		}
		return next - dest;
	}

#else
	template<class T1>
	inline static size_t serialize_(proto_base<T1> *data, unsigned char *dest, unsigned char *end) {
		T1 *entity = (T1*)data;
		return entity->serialize(entity, dest, end - dest);
	}

	template<class T1>
	inline static size_t serialize_(vector<T1> *data, unsigned char *dest, unsigned char *end) {
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_(&ele, next, end);
		}
		return next - dest;
	}

	template<class T1,class T2>
	inline static size_t serialize_(map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_((T1*)&ele.first, next, end);
			next += proto_field::serialize_(&ele.second, next, end);
		}
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t serialize_(unordered_map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_((T1*)&ele.first, next, end);
			next += proto_field::serialize_(&ele.second, next, end);
		}
		return next - dest;
	}

	template<class T1>
	inline static size_t serialize_(set<T1> *data, unsigned char *dest, unsigned char *end) {
		size_t size = data->size();
		OVERFLOW_CHECK(dest, end, varint_size(size));
		unsigned char *next = dest;
		next += varint_pack(size, next);
		for (auto &ele : *data) {
			next += proto_field::serialize_((T1*)&ele, next, end);
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
		memcpy(data, dest, SIZE_8_BYTE);
		return SIZE_8_BYTE;
	}

	inline static size_t unserialize_(fixed32 *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, SIZE_4_BYTE);
		memcpy(data, dest, SIZE_4_BYTE);
		return SIZE_4_BYTE;
	}

	template<class T>
	inline static size_t unserialize_(enumm<T> *data, const unsigned char *dest, const unsigned char *end) {
		return unserialize_(&(data->value), dest, end);
	}

#ifdef USE_TAG
	template<class T1>
	inline static size_t unserialize_(proto_base<T1> *data, const unsigned char *dest, const unsigned char *end) {
		T1 *entity = (T1*)data;
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		next += entity->unserialize(entity, next, end - next);
		return next - dest;
	}

	template<class T1>
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
			next += proto_field::unserialize_(&(*data)[index++], next, end);
		}
		data->resize(index);
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t unserialize_(map<T1, T2> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		const unsigned char *last = next + len;
		T1 key;
		while (next < last) {
			next += proto_field::unserialize_(&key, next, end);

			T2 &val = (*data)[key];
			next += proto_field::unserialize_(&val, next, end);
		}
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t unserialize_(unordered_map<T1, T2> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		const unsigned char *last = next + len;
		T1 key;
		while (next < last) {
			next += proto_field::unserialize_(&key, next, end);

			T2 &val = (*data)[key];
			next += proto_field::unserialize_(&val, next, end);
		}
		return next - dest;
	}

	template<class T1>
	inline static size_t unserialize_(set<T1> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		const unsigned char *last = next + len;
		T1 key;
		while (next < last) {
			next += proto_field::unserialize_(&key, next, end);
			data->insert(key);
		}
		return next - dest;
	}

#else
	template<class T1>
	inline static size_t unserialize_(proto_base<T1> *data, const unsigned char *dest, const unsigned char *end) {
		T1 *entity = (T1*)data;
		return entity->unserialize(entity, dest, end - dest);
	}

	template<class T1>
	inline static size_t unserialize_(vector<T1> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		data->resize(len);
		for (auto &ele : *data) {
			next += proto_field::unserialize_(&ele, next, end);
		}
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t unserialize_(map<T1, T2> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		T1 key;
		for (int i = 0; i < len; i++) {
			next += proto_field::unserialize_(&key, next, end);

			T2 &val = (*data)[key];
			next += proto_field::unserialize_(&val, next, end);
		}
		return next - dest;
	}

	template<class T1, class T2>
	inline static size_t unserialize_(unordered_map<T1, T2> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		T1 key;
		for (int i = 0; i < len; i++) {
			next += proto_field::unserialize_(&key, next, end);

			T2 &val = (*data)[key];
			next += proto_field::unserialize_(&val, next, end);
		}
		return next - dest;
	}

	template<class T1>
	inline static size_t unserialize_(set<T1> *data, const unsigned char *dest, const unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_scan(dest));
		const unsigned char *next = dest;
		size_t len;
		next += varint_unpack(next, &len);
		T1 key;
		for (int i = 0; i < len; i++) {
			next += proto_field::unserialize_(&key, next, end);
			data->insert(key);
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

	template<class T>
	inline static size_t size_(enumm<T> *data) {
		return size_(&(data->value));
	}

	template<class T1>
	inline static size_t size_(proto_base<T1> *data) {
		T1 *entity = (T1*)data;
		return entity->size(entity);
	}

#ifdef USE_TAG
	template<class T1>
	inline static size_t size_(vector<T1> *data) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_(&ele);
		}
		size += varint_size(size);
		return size;
	}

	template<class T1, class T2>
	inline static size_t size_(map<T1, T2> *data) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_((T1*)&ele.first);
			size += proto_field::size_(&ele.second);
		}
		size += varint_size(size);
		return size;
	}

	template<class T1, class T2>
	inline static size_t size_(unordered_map<T1, T2> *data) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_((T1*)&ele.first);
			size += proto_field::size_(&ele.second);
		}
		size += varint_size(size);
		return size;
	}

	template<class T1>
	inline static size_t size_(set<T1> *data) {
		size_t size = 0;
		for (auto &ele : *data) {
			size += proto_field::size_((T1*)&ele);
		}
		size += varint_size(size);
		return size;
	}

#else
	template<class T1>
	inline static size_t size_(vector<T1> *data) {
		return data->size();
	}

	template<class T1, class T2>
	inline static size_t size_(map<T1, T2> *data) {
		return data->size();
	}

	template<class T1, class T2>
	inline static size_t size_(unordered_map<T1, T2> *data) {
		return data->size();
	}

	template<class T1>
	inline static size_t size_(set<T1> *data) {
		return data->size();
	}
#endif // USE_TAG

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
		CHECK_DEFAULT(*data, 0);
		return false;
	}

	inline static bool is_default_(fixed64 *data) {
		CHECK_DEFAULT(*data, 0);
		return false;
	}

	template<class T>
	inline static bool is_default_(enumm<T> *data) {
		CHECK_DEFAULT(data->value, 0);
		return false;
	}
	
	template<class T1>
	inline static bool is_default_(proto_base<T1> *data) {
		T1 *entity = (T1*)data;
		return entity->is_default(entity);
	}

	template<class T1>
	inline static bool is_default_(vector<T1> *data) {
		CHECK_DEFAULT(data->size(), 0);
	}

	template<class T1, class T2>
	inline static bool is_default_(map<T1, T2> *data) {
		CHECK_DEFAULT(data->size(), 0);
	}

	template<class T1, class T2>
	inline static bool is_default_(unordered_map<T1, T2> *data) {
		CHECK_DEFAULT(data->size(), 0);
	}

	template<class T1>
	inline static bool is_default_(set<T1> *data) {
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
		*data = 0;
	}

	inline static void refresh_(fixed64 *data) {
		*data = 0;
	}

	template<class T>
	inline static void refresh_(enumm<T> *data) {
		data->value = 0;
	}

	template<class T1>
	inline static void refresh_(proto_base<T1> *data) {
		T1 *entity = (T1*)data;
		data->refresh(entity);
	}

	template<class T1>
	inline static void refresh_(vector<T1> *data) {
		data->clear();
	}

	template<class T1, class T2>
	inline static void refresh_(map<T1, T2> *data) {
		data->clear();
	}

	template<class T1, class T2>
	inline static void refresh_(unordered_map<T1, T2> *data) {
		data->clear();
	}

	template<class T1>
	inline static void refresh_(set<T1> *data) {
		data->clear();
	}

#pragma endregion

#pragma region type
	inline static WireType type_(bool *data) {
		return WireType_Varint;
	}

	inline static WireType type_(uint8_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(uint16_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(uint32_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(int8_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(int16_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(int32_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(uint64_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(int64_t *data) {
		return WireType_Varint;
	}

	inline static WireType type_(string *data) {
		return WireType_Varint;
	}

	inline static WireType type_(double *data) {
		return WireType_Fix64;
	}

	inline static WireType type_(float *data) {
		return WireType_Fix32;
	}

	inline static WireType type_(fixed32 *data) {
		return WireType_Fix32;;
	}

	inline static WireType type_(fixed64 *data) {
		return WireType_Fix64;
	}

	template<class T>
	inline static WireType type_(enumm<T> *data) {
		return WireType_Varint;
	}

	template<class T1>
	inline static WireType type_(proto_base<T1> *data) {
		return WireType_Length_Limited;
	}

	template<class T1>
	inline static WireType type_(vector<T1> *data) {
		return WireType_Length_Limited;
	}

	template<class T1, class T2>
	inline static WireType type_(map<T1, T2> *data) {
		return WireType_Length_Limited;
	}

	template<class T1, class T2>
	inline static WireType type_(unordered_map<T1, T2> *data) {
		return WireType_Length_Limited;
	}

	template<class T1>
	inline static WireType type_(set<T1> *data) {
		return WireType_Length_Limited;
	}
#pragma endregion
};


template<class T>
class proto_base
{
protected:
	DEFINE_ALL_OPERATER()

	size_t size_tag_(id_type id, WireType type) {
		id_type key = (id << WIRE_TYPE_LEN) | (id_type)type;
		return varint_size(key);
	}

	size_t serialize_tag_(id_type id, WireType type) {
		id_type key = (id << WIRE_TYPE_LEN) | (id_type)type;
		size_t size = varint_pack(key, next);
		next += size;
		return size;
	}

	size_t unserialize_tag_(id_type id, WireType type) {
		id_type key;
		size_t tag_size = varint_unpack(unnext, &key);
		id_type iid = key >> WIRE_TYPE_LEN;
		id_type kTagTypeMask = (1 << WIRE_TYPE_LEN) - 1;
		WireType ttype = WireType(key & kTagTypeMask);
		if (iid == id) {
			unnext += tag_size;
			if (type == ttype)
				return tag_size;
			else {
				if (ttype == WireType_Varint) {
					unnext += varint_scan(unnext);
				}
				else if (ttype == WireType_Fix32) {
					unnext += SIZE_4_BYTE;
				}
				else if (ttype == WireType_Fix64) {
					unnext += SIZE_8_BYTE;
				}
				else {
					size_t len = 0;
					unnext += (varint_unpack(unnext, &len) + len);
				}
				return 0;
			}
		}
		else {
			return 0;
		}
	}
public:
	size_t serialize(T *entity,unsigned char *nex, size_t size) {
		next = nex; 
		end = next + size;
		IMPL_OPERATER(entity, OP_SERIALIZE);
		return next - nex;
	}
	size_t unserialize(T *entity,const unsigned char *nex, size_t size) {
		unnext = nex;
		unend = unnext + size;
		IMPL_OPERATER(entity, OP_UNSERIALIZE);
		return unnext - nex;
	}
	size_t size(T *entity) {
		_size = 0;
		IMPL_OPERATER(entity, OP_SIZE);
		return _size;
	}
	static T &instance() {
		static T entity;
		return entity;
	}
	void refresh(T *entity) {
		IMPL_OPERATER(entity, OP_REFRESH);
	}
	bool is_default(T *entity) {
		_is_default = true;
		IMPL_OPERATER(entity, OP_DEFAULT);
		return _is_default;
	}
protected:
	unsigned char *next;
	unsigned char *end;
	const unsigned char *unnext;
	const unsigned char *unend;
	size_t _size;
	bool _is_default;
};