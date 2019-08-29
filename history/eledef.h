#pragma once

//#define number(TYPE,name,id)\
//						public:\
//							 TYPE name;\
//							 OVERRIDE_OPERATER(name,id,proto_field::type_(&name));\
//
//#define string(name,id,...) \
//						public:\
//							 string name;\
//							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
//
//
//#define msg(TYPE,name,id) \
//						public:\
//							 TYPE name;\
//							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
//
//#define enum(TYPE,name,id,...) \
//						public:\
//							 TYPE name;\
//						private:\
//							 enum_base tt_##name{(enum_base::value_type*)&name};\
//							 OVERRIDE_OPERATER(tt_##name,id,enum_base::type);\
//
//#define fixed(TYPE,name,id,...) \
//						public:\
//							 TYPE::value_type name;\
//						private:\
//							 TYPE tt_##name{&name};\
//							 OVERRIDE_OPERATER(tt_##name,id,TYPE::type);\
//
//#define vector(TYPE,name,id,...) \
//						public:\
//							 vector<TYPE> name;\
//							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
//
//#define map(KEY_TYPE,VAL_TYPE,name,id,...) \
//						public:\
//							 map<KEY_TYPE,VAL_TYPE> name;\
//							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
//
//#define unordered_map(KEY_TYPE,VAL_TYPE,name,id,...) \
//						public:\
//							 unordered_map<KEY_TYPE,VAL_TYPE> name;\
//							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
//
//#define set(TYPE,name,id,...) \
//						public:\
//							 set<TYPE> name;\
//							 OVERRIDE_OPERATER(name,id,WireType_Length_Limited);\
//;