#pragma once

#include "proto_base3.h"


_____CLASS_BEGIN(rigist)
NSM(int, tt, 1);
_____CLASS_END


_____CLASS_BEGIN(login2)
NSM(int32_t, i1, 1);
NSM(int64_t, thh, 2);
NSM(string, str, 3);
NSM(rigist, ttt, 4);
MAP(int, int, kkkk, 5);
VECTOR(rigist, vvv, 6);
_____CLASS_END

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
	function<void()> count;
};