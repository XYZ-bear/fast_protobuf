#pragma once

#include "proto_base5.h"


MESSAGE_BEGIN(rigist)
NSM(int, tt, 1);
END
#define and ,
#define fd(type,name) type name;



MESSAGE_BEGIN(login2)
NSM(int32_t, i1, 1);
NSM(int64_t, thh, 2);
NSM(string, str, 3);
NSM(rigist, ttt, 4);
MAP(int, int, kkkk, 5);
VECTOR(rigist, vvv, 6);
END

MESSAGE_BEGIN(Test)
NSM(string, str, 1);
NSM(int64_t, int64, 2);
NSM(int32_t, int32, 3);
NSM(uint32_t, uint32, 4);
NSM(int32_t, sint32, 5);
NSM(int64_t, sint64, 6);
NSM(double, fix64, 7);
NSM(float, fix32, 8);
NSM(double, doub, 9);
NSM(float, flo, 10);
NSM(bool, boo, 11);
MAP(int, int, mapp, 12);
VECTOR(int32_t, vec, 13);
NSM(rigist, rig, 14);
NSM(uint64_t, uint64, 15);
END

class Test2 :public rigist {
public:
	Test2() { DO_PRE_SET(); }
	Test2(const Test2 & c) { *this = c; DO_PRE_SET(); }
	NSM(uint64_t, uint64, 1);
};

class funct {
public:
	int a;
	funct() {
		count = []()->void {
			int a = 0;
			a++;
		};
		count2 = [this]()->void {
			a++;
		};
	}
protected:
	virtual void ccm() {
	}
	virtual void ccm2() {
	}
	function<void()> count;
	function<void()> count2;
};

#define DO_PRE_SET2() \
		ccm();\
ccm2();

class funct2:public proto_base {
public:
	int a;
	funct2() {
		ccm();
		ccm2();
	}
protected:
	void ccm() {
	}
	void ccm2() {
	}
};

class funct3 :public proto_base {
public:
	funct3() {
		ccm();
		ccm2();
	}
protected:
	void ccm() {
	}
	void ccm2() {
	}
};

class funct4 :public funct2,funct3 {
public:
	funct4() {
		DO_PRE_SET2();
	}
protected:
	void ccm() {
	}
	void ccm2() {
	}
};