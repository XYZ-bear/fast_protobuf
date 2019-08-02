#pragma once

#include <vector>
#include <map>
#include <string>
using namespace std;

#define   MAX_VARINT32_BYTES   5
#define   MAX_UINT8            256
#define   MAX_UINT16           65536
#define   MAX_UINT24           16777216
#define   MAX_UINT32           4294967296

#define BUILD(class_name) class_name(){}
#define RF(TYPE,name,id) void check_##id()=delete;\
                         bool has_##name(){ return has_field(id);}\
                         void set_##name(TYPE name_v){ set_field(id,name_v);}\
                         TYPE get_##name(){TYPE res;get_filed(id,res);return res;}

#define SET_MSG(TYPE,name,id) void check_##id()=delete;\
                         bool has_##name(){ return has_field(id);}\
                         void set_##name(TYPE &name_v){ set_msg_field(id,name_v);}\
                         TYPE &get_##name(){TYPE res;get_filed(id,res);return res;}

struct tt {
	int kk;
	int jj;
	string a;
};

class proto_base
{
public:
	struct field_info {
		short len;
		short pos;
	};
	enum WireType {
		WIRETYPE_VARINT = 0,
		WIRETYPE_FIXED64 = 1,
		WIRETYPE_LENGTH_DELIMITED = 2,
		WIRETYPE_START_GROUP = 3,
		WIRETYPE_END_GROUP = 4,
		WIRETYPE_FIXED32 = 5,
		WIRETYPE_SELFTYPE = 6,
		WIRETYPE_MSGTYPE = 7,
	};
private:
	template<class T>
	inline uint8_t *varint_encode_uint32(T value, uint8_t * target) { return nullptr; };
	inline uint8_t *varint_encode_uint32(uint32_t value, uint8_t * target)
	{
		target[0] = (uint8_t)(value | 0x80);

		if (value >= (1 << 7))
		{
			target[1] = (uint8_t)((value >> 7) | 0x80);

			if (value >= (1 << 14))
			{
				target[2] = (uint8_t)((value >> 14) | 0x80);

				if (value >= (1 << 21))
				{
					target[3] = (uint8_t)((value >> 21) | 0x80);

					if (value >= (1 << 28))
					{
						target[4] = (uint8_t)(value >> 28);
						return target + 5;
					}
					else
					{
						target[3] &= 0x7F;
						return target + 4;
					}
				}
				else
				{
					target[2] &= 0x7F;
					return target + 3;
				}
			}
			else
			{
				target[1] &= 0x7F;
				return target + 2;
			}
		}
		else
		{
			target[0] &= 0x7F;
			return target + 1;
		}
	}

	/**
	* 从buf中 将 varint压缩编码的值 还原读取出来
	* 需要确保输入的buf 从 输出的指针到结尾 超过  5个byte, 避免出现core
	* 函数内部不做边界检查
	*
	* @param buffer    输入的buf
	* @param value     输出的值
	*
	* @return  target中下一个可读的字节位置
	*/
	template<class T>
	inline const void varint_decode_uint32(const uint8_t * buffer, T * value) {}
	inline const uint8_t *varint_decode_uint32(const uint8_t * buffer, uint32_t * value)
	{
		const uint8_t * ptr = buffer;

		uint32_t  i = 0;
		uint32_t  b;
		uint32_t  result;

		b = *(ptr++); result = (b & 0x7F); if (!(b & 0x80)) goto done;
		b = *(ptr++); result |= (b & 0x7F) << 7; if (!(b & 0x80)) goto done;
		b = *(ptr++); result |= (b & 0x7F) << 14; if (!(b & 0x80)) goto done;
		b = *(ptr++); result |= (b & 0x7F) << 21; if (!(b & 0x80)) goto done;
		b = *(ptr++); result |= b << 28; if (!(b & 0x80)) goto done;

		for (; i < MAX_VARINT32_BYTES; i++)
		{
			b = *(ptr++); if (!(b & 0x80)) goto done;
		}

		return NULL;
	done:
		*value = result;
		return ptr;
	}

	inline uint32_t zigZag_encode32(int32_t  n) { return (n << 1) ^ (n >> 31); }
	inline uint64_t zigZag_encode64(int64_t  n) { return (n << 1) ^ (n >> 63); }

	/**
	* 对整数进行 zigZag 解码，  无符号数 转换为 有符号数
	*
	* @param n  无符号数
	*
	* @return   有符号数
	*/
	inline int32_t  zigZag_decode32(uint32_t n) { return (n >> 1) ^ -(int32_t)(n & 1); }
	inline int64_t  zigZag_decode64(uint64_t n) { return (n >> 1) ^ -(int64_t)(n & 1); }
protected:
	template<class T>
	WireType get_wire_type(T &a) {
		if (typeid(T) == typeid(int32_t) ||
			typeid(T) == typeid(int64_t) ||
			typeid(T) == typeid(uint32_t) ||
			typeid(T) == typeid(uint64_t) ||
			typeid(T) == typeid(bool) ||
			typeid(T) == typeid(WireType) )
		{
			return WIRETYPE_VARINT;
		}
		else if (typeid(T) == typeid(double))
		{
			return WIRETYPE_FIXED64;
		}
		else if (typeid(T) == typeid(float)) {
			return WIRETYPE_FIXED32;
		}
		else if (typeid(T) == typeid(string)) {
			return WIRETYPE_LENGTH_DELIMITED;
		}
		else {
			proto_base *pb = reinterpret_cast<proto_base *>(&a);
			if (pb->get_self_type() == WIRETYPE_MSGTYPE)
				return WIRETYPE_MSGTYPE;
			return WIRETYPE_SELFTYPE;
		}
	}

	WireType get_self_type() {
		return self_type_;
	}

	bool has_field(short id) {
		if (fields_.find(id) == fields_.end())
			return false;
		return true;
	}

	void set_field(short id, string a) {
		char key = (id << 3) | (char)WIRETYPE_LENGTH_DELIMITED;
		memcpy(next_field_, &key, sizeof(char));
		next_field_ += 1;
		fields_[id] = next_field_;
		next_field_ = varint_encode_uint32(a.size(), next_field_);
		memcpy(next_field_, a.c_str(), sizeof(char)*a.size());
		next_field_ += sizeof(char)*a.size();
	}
	
	template<class T>
	void set_field(short id,T a) {
		WireType wire_type = get_wire_type<T>(a);
		char key=(id << 3) | (char)wire_type;
		memcpy(next_field_ , &key, sizeof(char));
		next_field_ += 1;
		fields_[id] = next_field_;    
		if (wire_type == WIRETYPE_VARINT) {
			next_field_ = varint_encode_uint32(a, next_field_);
		}
		else if (wire_type == WIRETYPE_SELFTYPE) {
			next_field_ = varint_encode_uint32(sizeof(T), next_field_);
			memcpy(next_field_, &a, sizeof(T));
			next_field_ += sizeof(T);
		}
		else if (wire_type == WIRETYPE_MSGTYPE) {
			proto_base *pb = reinterpret_cast<proto_base *>(&a);
			uint32_t size = (uint32_t)pb->get_size();
			next_field_ = varint_encode_uint32(size, next_field_);
			memcpy(next_field_, pb->get_buff(), size);
			next_field_ += size;
		}
		else{
			memcpy(next_field_, &a, sizeof(T));
			next_field_ += sizeof(T);
		}
	}

	void get_filed(short id,string &res) {
		uint32_t len;
		const unsigned char*next_field = varint_decode_uint32(fields_[id], &len);
		res.assign((char*)(next_field), len);
	}

	template<class T>
	void get_filed(short id,T &res) {
		WireType wire_type = get_wire_type<T>(res);
		if (wire_type == WIRETYPE_VARINT) {
			varint_decode_uint32(fields_[id], &res);
			return;
		}
		else if (wire_type == WIRETYPE_MSGTYPE) {
			uint32_t size;
			const unsigned char*next_field = varint_decode_uint32(fields_[id], &size);
			proto_base *pb = reinterpret_cast<proto_base *>(&res);
			pb->unerialize(next_field, size);
			return;
		}
		else if (wire_type == WIRETYPE_SELFTYPE) {
			uint32_t size;
			const unsigned char*next_field = varint_decode_uint32(fields_[id], &size);
			memcpy(&res, next_field, size);
			return;
		}
		else {
			res = *(T*)(fields_[id]);
		}
	}

	template<class T>
	void set_msg_field(short id, T &a) {
		char key = (id << 3) | (char)WIRETYPE_MSGTYPE;
		memcpy(next_field_, &key, sizeof(char));
		next_field_ += 1;
		fields_[id] = next_field_;
		uint32_t size = (uint32_t)a.get_size();
		next_field_ = varint_encode_uint32(size, next_field_);
		memcpy(next_field_, a.get_buff(), size);
		next_field_ += size;
	}

	template<class T>
	void get_msg_filed(short id, T &res) {
		uint32_t size;
		const unsigned char*next_field = varint_decode_uint32(fields_[id], &size);
		res.unerialize(next_field, size);
	}

	unsigned char*next_field_;
	unsigned char*begin_field_;
	map<short, unsigned char*> fields_;
	int len_;
	WireType self_type_;
	unsigned char value[1000];
public:
	void unerialize(const unsigned char *val,int size) {
		memcpy(value, val, size);
		uint32_t res;
		const unsigned char*next_field = value;
		while((next_field-value)<size){
			char key = *(char*)(next_field);
			short id = (key >> 3);
			next_field += sizeof(char);
			fields_[id] = const_cast<unsigned char*>(next_field);
			WireType wire_type = (WireType)(key ^ (id << 3));
			if (wire_type == WIRETYPE_VARINT) {
				next_field = varint_decode_uint32(next_field, &res);
			}
			else if (wire_type == WIRETYPE_SELFTYPE) {
				next_field = varint_decode_uint32(next_field, &res);
				fields_[id] = const_cast<unsigned char*>(next_field);
				next_field += res;
			}
			else if (wire_type == WIRETYPE_MSGTYPE) {
				uint32_t size;
				next_field = varint_decode_uint32(next_field, &size);
				next_field += size;
			}
			else if (wire_type == WIRETYPE_LENGTH_DELIMITED) {
				uint32_t size;
				next_field = varint_decode_uint32(next_field, &size);
				next_field += size;
			}
			else if (wire_type == WIRETYPE_FIXED64) {
				next_field += size;
			}
			else if (wire_type == WIRETYPE_FIXED32) {
				next_field += 4;
			}
		}
	}
	const unsigned char* get_buff() {
		return value;
	}

	int get_size() {
		return next_field_ - begin_field_;
	}

	proto_base() {
		self_type_ = WIRETYPE_MSGTYPE;
		begin_field_ = value;
		next_field_ = value;
		len_ = 0;
	};
	~proto_base();
};

class rigist :public proto_base {
public:
	RF(uint32_t, tt, 1);
};

class login :public proto_base {
public:
	RF(uint32_t, dex, 1);
	RF(int, na, 2);
	RF(double, df, 3);
	RF(tt, paa, 4);
	RF(string, str, 5);
	SET_MSG(rigist, ttt, 6);
};
