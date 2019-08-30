#pragma once
#include <stdint.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <set>
#include "fast_common.h"
#include "serializer.h"
using namespace std;

#ifdef UNION_TYPE3
#undef UNION_TYPE3
#endif

#ifdef UNION_TYPE4
#undef UNION_TYPE4
#endif

string class_name = "";

#define enum(name,...)\
enum_collector enum_collector_##name{class_name,#name,#__VA_ARGS__};\
enum name{\
    __VA_ARGS__\
};

#define MESSAGE(class_name) class class_name:public message<class_name>

#define UNION_TYPE3(t1, name, id) \
private:\
field_collector<t1> field_collector_##name{class_name,#t1,#name,id};\
void use_it_##name() { get_instance(); }

#define UNION_TYPE4(t1, t2, name, id) \
private:\
field_collector<t1,##t2> field_collector_##name{class_name,"",#name,id};\
void use_it_##name() { get_instance(); }

#define ele(...) INVOKE_VAR_MACRO(UNION_TYPE, __VA_ARGS__)

class cshrap_type_map;

template<class T>
class message;


class cshrap_type_map {
public:
	inline static string type(bool *data,string name="") {
		return "bool";
	}
	inline static string type(uint8_t *data, string name = "") {
		return "Byte";
	}
	inline static string type(uint16_t *data, string name = "") {
		return "Int16";
	}
	inline static string type(uint32_t *data, string name = "") {
		return "UInt32";
	}
	inline static string type(int8_t *data, string name = "") {
		return "SByte";
	}
	inline static string type(int16_t *data, string name = "") {
		return "Int16";
	}
	inline static string type(int32_t *data, string name = "") {
		return "Int32";
	}
	inline static string type(uint64_t *data, string name = "") {
		return "UInt64";
	}
	inline static string type(int64_t *data, string name = "") {
		return "Int64";
	}
	inline static string type(string *data, string name = "") {
		return "String";
	}
	inline static string type(double *data, string name = "") {
		return "Double";
	}
	inline static string type(float *data, string name = "") {
		return "float";
	}
	inline static string type(fixed64 *data, string name = "") {
		return "Fixex64";
	}
	inline static string type(fixed32 *data, string name = "") {
		return "Fixex32";
	}
	template<class T>
	inline static string type(T *data, string name = "") {
		return name;
	}
	template<class T>
	inline static string type(enumm<T> *data, string name = "") {
		return name;
	}
	template<class T1>
	inline static string type(vector<T1> *data, string name = "") {
		T1 *val = nullptr;
		return "List<"+ type(val)+">";
	}
	template<class T1, class T2>
	inline static string type(map<T1, T2> *data, string name = "") {
		T1 *key = nullptr;
		T2 *val = nullptr;
		return "Dictionary<" + type(key) + "," + type(val) + ">";
	}
	template<class T1, class T2>
	inline static string type(unordered_map<T1, T2> *data, string name = "") {
		T1 *key = nullptr;
		T2 *val = nullptr;
		return "Dictionary<" + type(key) + "," + type(val) + ">";
	}
	template<class T1>
	inline static string type(set<T1> *data, string name = "") {
		T1 *val = nullptr;
		return "HashSet<" + type(val) + ">";
	}
};

class collector {
public:
	static collector & get_instance() {
		static collector mm;
		return mm;
	}

	void set_field(string class_name,string type,string name, size_t id) {
		fields[class_name][id] = field{ type,name };
	}

	void set_enum(string class_name,string name, string val) {
		enums[class_name].push_back(enum_t{ name,val });
	}

	struct field
	{
		string type;
		string name;
	};

	struct enum_t
	{
		string name;
		string val;
	};

	bool generate_csharp(string nps_name) {
		ofstream f("message_csharp.cs");
		if (!f)return false;
		f << "using System;" << endl;
		f << "using System.Collections;" << endl;
		f << "using System.Collections.Generic;" << endl << endl;
		
		f << "namespace " << nps_name << endl;
		f << "{" << endl;

		for (auto &en : enums) {
			if (en.first == "") {
				for (auto &info : en.second)
					f << "	enum " << info.name << "{" << info.val << "}" << endl;
			}
		}

		for (auto &field : fields) {
			f << "	" << field.first << endl;
			f << "	{" << endl;

			for (auto &info : enums[field.first]) {
				f << "		enum " << info.name << "{" << info.val << "}" << endl;
			}

			for (auto &info : field.second) {
				f << "		public " << info.second.type << " " << info.second.name << ";//" << info.first << endl;
			}
			f << "	}" << endl << endl;
		}
		f << "}" << endl;
		return true;
	}
private:
	map<string, map<size_t,field>> fields;
	map<string, vector<enum_t>> enums;
};

template<class T>
class field_collector {
public:
	field_collector(string class_name, string type, string name, size_t id) {
		T *val = nullptr;
		collector::get_instance().set_field(class_name, cshrap_type_map::type(val, type), name, id);
	}
};

class enum_collector {
public:
	enum_collector(string class_name,string name, string val) {
		collector::get_instance().set_enum(class_name, name, val);
	}
};


template<class T>
class message{
private:
	static T mod;
public:
	typedef T module_type;
	message() {
		class_name = typeid(T).name();
		T *entity = &mod;
	}
	T & get_instance() {
		return mod;
	}
	string class_name;
};

template<class T>
T message<T>::mod;