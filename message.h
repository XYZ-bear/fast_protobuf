#pragma once

#include "fast_protobuf.h"


MESSAGE_BEGIN(rigist)
NSM(int, tt, 1);
END

enum ennn
{
	type=-1
};

MESSAGE_BEGIN(login2)
NSM(int32_t, i1, 1);
NSM(int64_t, thh, 2);
NSM(string, str, 3);
NSM(rigist, ttt, 4);
MAP(int, int, kkkk, 5);
VECTOR(rigist, vvv, 6);
NSM(double, dou, 7);
NSM(bool, boo, 8);
ENUM(ennn, ev, 9);
END

MESSAGE_BEGIN(login3)
NSM(int32_t, i1, 1);
NSM(int64_t, thh, 2);
NSM(string, str, 3);
NSM(rigist, ttt, 4);
MAP(int, int, kkkk, 5);
VECTOR(rigist, vvv, 6);
END

class funct {
public:
	funct() {
		count = []()->void{
			int a = 0;
			a++;
		};
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