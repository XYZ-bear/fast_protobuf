#pragma once
#include "option.h"


//MESSAGE(rigist) {
//	NSM(int, tt, 1);
//};
//
//MESSAGE(login2) {
//	NSM(int32_t, i1, 1);
//	NSM(int64_t, thh, 2);
//	NSM(string, str, 3);
//	NSM(rigist, ttt, 4);
//	MAP(int, int, kkkk, 5);
//	VECTOR(rigist, vvv, 6);
//};
//
//MESSAGE(Test) {
//	NSM(string, str, 1);
//	NSM(int64_t, int64, 2);
//	NSM(int32_t, int32, 3);
//	NSM(uint32_t, uint32, 4);
//	NSM(int32_t, sint32, 5);
//	NSM(int64_t, sint64, 6);
//	//NSM(double, fix64, 7);
//	//NSM(float, fix32, 8);
//	NSM(double, doub, 9);
//	NSM(float, flo, 10);
//	NSM(bool, boo, 11);
//	//MAP(int, int, mapp, 12);
//	VECTOR(int32_t, vec, 13);
//	NSM(rigist, rig, 14);
//	NSM(uint64_t, uint64, 15);
//	FIXED(fixed32, fi32, 16);
//	FIXED(fixed64, fi64, 17);
//};
//
//MESSAGE(Test1) {
//	NSM(string, str, 1);
//	NSM(int64_t, int64, 2);
//	NSM(int32_t, int32, 3);
//	NSM(uint32_t, uint32, 4);
//	NSM(int32_t, sint32, 5);
//	NSM(int64_t, sint64, 6);
//	NSM(double, fix64, 7);
//	NSM(float, fix32, 8);
//	NSM(double, doub, 9);
//	NSM(float, flo, 10);
//	NSM(bool, boo, 11);
//	MAP(int, int, mapp, 12);
//	VECTOR(int32_t, vec, 13);
//	NSM(rigist, rig, 14);
//	NSM(uint64_t, uint64, 15);
//	FIXED(fixed32, fi32, 16);
//	FIXED(fixed64, fi64, 17);
//};
//
//MESSAGE_(Test2,Test) {
//	NSM(string, str2, 1);
//};

MESSAGE(rigist) {
	ele(int, tt, 1);
};

#define _ ,

MESSAGE(Test) {
	//STRING(string, str, 1);
	//NUMBER(int64_t, int64, 2);
	//NUMBER(int32_t, int32, 3);
	//NUMBER(uint32_t, uint32, 4);
	//NUMBER(int32_t, sint32, 5);
	//NUMBER(int64_t, sint64, 6);
	//DOUBLE(double, doub, 9);
	//FLOAT(float, flo, 10);
	//NUMBER(bool, boo, 11);
	////MAP(int, int, mapp, 12);
	//VECTOR(int32_t, vec, 13);
	//MSG(rigist, rig, 14);
	//NUMBER(uint64_t, uint64, 15);
	//FIXED(fixed32, fi32, 16);
	//FIXED(fixed64, fi64, 17);
public:
	enum ttten
	{
		Hello=-100,
		Bitch = 100,
	};
	ele(string, str, 1);
	ele(int64_t, int64, 2);
	ele(int32_t, int32, 3);
	ele(uint32_t, uint32, 4);
	ele(int32_t, sint32, 5);
	ele(int64_t, sint64, 6);
	ele(double,doub, 9);
	ele(float,flo, 10);
	ele(bool, boo, 11);
	ele(map<int, int>, mapp, 12);
	ele(vector<int32_t>, vec, 13);
	ele(rigist, rig, 14);
	ele(uint64_t, uint64, 15);
	ele(fixed32, fi32, 16);
	ele(fixed64, fi64, 17);
	ele(enumm<ttten>, ttte, 18);
};

MESSAGE(Test2) {
	enum ttten
	{
		Hello = -100,
		Bitch = 100,
	};
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
	//ele(map<int, vector<int>>, hhha, 19);
};


MESSAGE(Test4) {
	//map(int, vector<int>, tt, 1);
};
//MESSAGE_(Test2, Test) {
//	STRING(string, str2, 1);
//};

class funct {
public:
	funct() {
	}
	void ccm() {
		int a = 0;
		a++;
	}
	void ccm(int h) {
		int a = 0;
		a++;
	}
	void ccm(float h) {
		int a = 0;
		a++;
	}
	void fj(int type) {
		if (type == 1)
			ccm(1);
		else if (type == 2)
			ccm(1.22f);
	}
	function<void()> count;
	using aa = int;
};

class funct2:public funct {
public:
	funct2() {
	}
	 void ccm() {
		int a = 0;
		a++;
	}
};
