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

#define ENUM(TYPE,name,id,...) \
						private:\
							 TYPE name;\
							 void set_##id(){set_enum_field<TYPE>(&name,id);}\
						public:\
							 void set_##name(TYPE val){ name=val;}\
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

#define MESSAGE_BEGIN(class_name)\
class class_name:public proto_base{\
public:\
class_name(){DO_PRE_SET();}\
class_name(const class_name & c){*this=c;DO_PRE_SET();}\

#define END };

#define OVERFLOW_CHECK(begin,end,size) if ((begin+size) > end) return 0;

#define CHECK_DEFAULT(data,default_value) if(data==default_value) return true;else return false;

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

class proto_base;

class field_base {
public:
	virtual size_t serialize(unsigned char *begin, unsigned char *end) = 0;
	virtual size_t unserialize(const unsigned char *begin, const unsigned char *end) = 0;
	virtual size_t size() = 0;
	virtual bool   is_default() = 0;
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
		OVERFLOW_CHECK(dest , end, varint_size(*(uint32_t*)data));
		return varint_pack(*(uint32_t*)data, dest);
	}
	inline static size_t serialize_(uint32_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest , end, varint_size(*data));
		return varint_pack(*data, dest);
	}
	inline static size_t serialize_(int8_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest , end, SIZE_1_BYTE);
		memcpy(dest, data, SIZE_1_BYTE);
		return SIZE_1_BYTE;
	}
	inline static size_t serialize_(int16_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(zigZag_encode(*(int32_t*)data)));
		return varint_pack(zigZag_encode(*(int32_t*)data), dest);
	}
	inline static size_t serialize_(int32_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(zigZag_encode(*data)));
		return varint_pack(zigZag_encode(*data), dest);
	}
	inline static size_t serialize_(uint64_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(*data));
		return varint_pack(*data, dest);
	}
	inline static size_t serialize_(int64_t *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(zigZag_encode(*data)));
		return varint_pack(zigZag_encode(*data), dest);
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
	inline static size_t serialize_(proto_base *data, unsigned char *dest, unsigned char *end) {
		return data->serialize(dest, end - dest);
	}
	inline static size_t serialize_(vector<T1> *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(data->size()));
		unsigned char *next = dest;
		next += varint_pack(data->size(), next);
		for (auto &ele : *data) {
			next += proto_field<T1>::serialize_(&ele, next, end);
		}
		return next - dest;
	}
	inline static size_t serialize_(map<T1, T2> *data, unsigned char *dest, unsigned char *end) {
		OVERFLOW_CHECK(dest, end, varint_size(data->size()));
		unsigned char *next = dest;
		next += varint_pack(data->size(), next);
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
	inline static size_t unserialize_(proto_base *data, const unsigned char *dest, const unsigned char *end) {
		return data->unserialize(dest, end - dest);
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
		for (size_t i = 0; i < len; i++) {
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
		return varint_size(dest, data);
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
	inline static size_t size_(proto_base *data) {
		return data->size();
	}
	inline static size_t size_(vector<T1> *data) {
		size_t size = 0;
		size += varint_size(data->size());
		for (auto &ele : *data) {
			size += proto_field<T1>::size_(&ele);
		}
		return size;
	}
	inline static size_t size_(map<T1, T2> *data) {
		size_t size = 0;
		size += varint_size(data->size());
		for (auto &ele : *data) {
			size += proto_field<T1>::size_((T1*)&ele.first);
			size += proto_field<T2>::size_(&ele.second);
		}
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
	inline static bool is_default_(proto_base *data) {
		CHECK_DEFAULT(data->with_ids_size(), 0);
	}
	inline static bool is_default_(vector<T1> *data) {
		CHECK_DEFAULT(data->size(), 0);
	}
	inline static bool is_default_(map<T1, T2> *data) {
		CHECK_DEFAULT(data->size(), 0);
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
private:
	Container * data_;
};



class proto_base
{
public:
	~proto_base() {
		for (auto field : proto_fields_) {
			delete field;
		}
	}

	//顶层值拷贝，meta信息保留，不进行拷贝
	void operator=(const proto_base &c) {
	}

	size_t unserialize(const unsigned char *val,size_t size) {
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

	size_t serialize(unsigned char *dest,size_t size) {
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

protected:
	template<class T>
	void set_field(T *a, uid_t id, bool isrequird = false, bool enable = true) {
		proto_field<T> *pb = new proto_field<T>;
		pb->set_data(a);
		proto_fields_.push_back(pb);
	}

	template<class T>
	void set_enum_field(T *a, uid_t id) {
		if (sizeof(T) <= SIZE_4_BYTE) {
			proto_field<int32_t> *pb = new proto_field<int32_t>;
			pb->set_data((int32_t*)a);
			proto_fields_.push_back(pb);
		}
		else {
			proto_field<int64_t> *pb = new proto_field<int64_t>;
			pb->set_data((int64_t*)a);
			proto_fields_.push_back(pb);
		}
	}

	template< class T, class Contianer = vector<T>>
	void set_vector_field(uid_t id, Contianer *a, bool isrequird = false, bool enable = true) {
		proto_field<T, T, Contianer> *pb = new proto_field<T, T, Contianer>;
		pb->set_data(a);
		proto_fields_.push_back(pb);
	}

	template<class T1, class T2, class Contianer = map<T1, T2>>
	void set_map_field(uid_t id, Contianer *a, bool isrequird = false, bool enable = true) {
		proto_field<T1, T2, Contianer> *pb = new proto_field<T1, T2, Contianer>;
		pb->set_data(a);
		proto_fields_.push_back(pb);
	}

	DEFINE_ALL_PRE_SET()
public:
	size_t serialize_ids_(unsigned char *next, size_t size) {
		char Bit_bit[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
		char ids = 0;
		size_t ids_byte_len = (proto_fields_.size() / SIZE_8_BYTE + 1);
		if (ids_byte_len > size)
			return 0;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			if (!proto_fields_[i]->is_default())
				ids |= Bit_bit[i % SIZE_8_BYTE];
			if (i != 0 && i % SIZE_8_BYTE == 0) {
				memcpy(next, &ids, SIZE_1_BYTE);
				next++;
				ids = 0;
			}
		}
		memcpy(next, &ids, SIZE_1_BYTE);
		return ids_byte_len;
	}

	size_t unserialize_ids_(const unsigned char *next, size_t size) {
		char Bit_bit[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
		size_t ids_byte_len = (proto_fields_.size() / SIZE_8_BYTE + 1);
		if (ids_byte_len > size)
			return 0;
		size_t id = 0;
		size_t byte_id = 0;
		while (id != proto_fields_.size()) {
			if (next[byte_id] & Bit_bit[id%SIZE_8_BYTE])
				int ag;
			if (id != 0 && id%SIZE_8_BYTE == 0)
				byte_id++;
			id++;
		}
		return ids_byte_len;
	}

	size_t serialize_with_ids_(unsigned char *next, size_t size) {
		unsigned char*end = next + size;
		char Bit_bit[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
		char ids = 0;
		size_t t_size = (proto_fields_.size() / SIZE_8_BYTE + 1);
		unsigned char *data_next = next + t_size;
		if (t_size > size)
			return 0;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			if (!proto_fields_[i]->is_default()) {
				ids |= Bit_bit[i % SIZE_8_BYTE];
				data_next += proto_fields_[i]->serialize(data_next, end);
			}
			if (i != 0 && i % SIZE_8_BYTE == 0) {
				memcpy(next, &ids, SIZE_1_BYTE);
				next++;
				ids = 0;
			}
		}
		memcpy(next, &ids, SIZE_1_BYTE);
		return data_next - next;
	}

	size_t unserialize_with_ids_(const unsigned char *next, size_t size) {
		const unsigned char*end = next + size;
		char Bit_bit[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
		size_t t_size = (proto_fields_.size() / SIZE_8_BYTE + 1);
		if (t_size > size)
			return 0;
		size_t id = 0;
		size_t byte_id = 0;
		const unsigned char *data_next = next + t_size;
		while (id != proto_fields_.size()) {
			if (next[byte_id] & Bit_bit[id%SIZE_8_BYTE]) {
				if (size_t t_s = proto_fields_[id]->unserialize(data_next, end)) {
					t_size += t_s;
					data_next += t_s;
				}
				else
					return false;
			}
			if (id != 0 && id%SIZE_8_BYTE == 0)
				byte_id++;
			id++;
		}
		return t_size;
	}

	size_t with_ids_size() {
		size_t size = 0;
		for (size_t i = 0; i < proto_fields_.size(); i++) {
			if (!proto_fields_[i]->is_default()) {
				size += proto_fields_[i]->size();
			}
		}
		return size;
	}
private:
	vector<field_base*> proto_fields_;
};