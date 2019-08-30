#pragma once

#if defined(SPEED_256)

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <set>
#include "operater.h"
#include "fast_common.h"
#include "fast_field.h"
using namespace std;

#ifdef ele
#undef ele
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

#ifdef enum
#undef enum
#endif

#define enum(name,...) enum name{__VA_ARGS__};

#define UNION_TYPE3(t1, name, id) \
						public:\
							t1 name;\
							OVERRIDE_OPERATER(name,id,proto_field::type_(&name));

#define UNION_TYPE4(t1, t2, name, id) \
						public:\
							t1,##t2 name;\
							OVERRIDE_OPERATER(name,id,proto_field::type_(&name));

#define ele(...) INVOKE_VAR_MACRO(UNION_TYPE, __VA_ARGS__);

#define MESSAGE(class_name)\
	class class_name:public proto_base<class_name>\

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
	size_t serialize(unsigned char *nex, size_t size) {
		T *entity = (T*)this;
		next = nex;
		end = next + size;
		IMPL_OPERATER(entity, OP_SERIALIZE);
		return next - nex;
	}
	size_t unserialize(const unsigned char *nex, size_t size) {
		T *entity = (T*)this;
		unnext = nex;
		unend = unnext + size;
		IMPL_OPERATER(entity, OP_UNSERIALIZE);
		return unnext - nex;
	}
	size_t size() {
		T *entity = (T*)this;
		_size = 0;
		IMPL_OPERATER(entity, OP_SIZE);
		return _size;
	}
	static T &instance() {
		static T entity;
		return entity;
	}
	static T &refresh_instance() {
		static T entity;
		entity.refresh();
		return entity;
	}
	void refresh() {
		T *entity = (T*)this;
		IMPL_OPERATER(entity, OP_REFRESH);
	}
	bool is_default() {
		T *entity = (T*)this;
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

#endif // SPEED_256