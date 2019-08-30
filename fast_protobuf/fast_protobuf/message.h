#pragma once
#include "fast_protobuf.h"

MESSAGE(rigist) {
	ele(int, tt, 1);
};

MESSAGE(Test) {
public:
	enum(ttten, Hello = -100, Bitch = 100);
	ele(string, str, 1);
	ele(int64_t, int64, 2);
	ele(int32_t, int32, 3);
	ele(uint32_t, uint32, 4);
	ele(int32_t, sint32, 5);
	ele(int64_t, sint64, 6);
	ele(double, doub, 9);
	ele(float, flo, 10);
	ele(bool, boo, 11);
	ele(map<int, int>, mapp, 12);
	ele(vector<int32_t>, vec, 13);
	ele(rigist, rig, 14);
	ele(uint64_t, uint64, 15);
	ele(fixed32, fi32, 16);
	ele(fixed64, fi64, 17);
	ele(enumm<ttten>, ttte, 18);
};

MESSAGE(Simple) {
	ele(string, str, 1);
	ele(int64_t, int64, 2);
	ele(int32_t, int32, 3);
	ele(uint32_t, uint32, 4);
	ele(int32_t, sint32, 5);
	ele(int64_t, sint64, 6);
	ele(double, doub, 7);
	ele(float, flo, 8);
	ele(bool, boo, 9);
	ele(rigist, rig, 10);
	ele(uint64_t, uint64, 11);
	ele(fixed32, fi32, 12);
	ele(fixed64, fi64, 13);
};