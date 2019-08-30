#pragma once

// GENERATE_CODE ���������������Դ���
// SPEED_256 һ��message�����ֶ�256��������ģʽ�����ٶȷǳ��ĸߡ�
//           ����һ�������Ƶ�ģʽ�������ٶȲ�һЩ������google��protobuf�ӽ�
// USE_TAG //�������л���ʽ����Tag�Ͳ���Tag

//--------------------------------------------------------------------------
//#define GENERATE_CODE
//--------------------------------------------------------------------------

#ifdef GENERATE_CODE
	#include "collector.h"
#else
	//--------------------------------------------------------------------------
	#define SPEED_256
	//#define SPEED_UNLIMITE
	//#define USE_TAG
    //--------------------------------------------------------------------------

	#include "fast_protobuf_256.h"
	#include "fast_protobuf_unlimit.h"

	#ifdef USE_TAG
	#define OVERRIDE_OPERATER(ele,id,type) \
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
#endif // GENERATE_CODE

