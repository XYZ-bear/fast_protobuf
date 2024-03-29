#pragma once
#include <iostream>
#include <functional>
#include "message.h"
#include <ctime>


#define _CRT_SECURE_NO_WARNINGS

void test(string name, size_t t, function<void(size_t t)> f) {
	clock_t startTime, endTime;
	startTime = clock();
	f(t);
	endTime = clock();
	cout << name << "|"<< endTime - startTime << "ms" << endl ;
}

#if defined(SPEED_256)|| defined(SPEED_UNLIMITE)
void test_fast(size_t run_times) {
	cout << run_times << "次" << endl;
	test("简单构造与析构", run_times, [](size_t t)->void {
		for (size_t i = 0; i < t; i++) {
			Simple test;
		}
	});
	test("复杂构造与析构", run_times, [](size_t t)->void {
		for (size_t i = 0; i < t; i++) {
			Test test;
		}
	});
	test("赋值", run_times, [](size_t t)->void {
		for (size_t i = 0; i < t; i++) {
			Test test;
			test.boo = true;
			test.int32 = 32;
			test.int64 = 641;
			test.sint32 = 232;
			test.sint64 = 264;
			test.uint32 = 632;
			test.uint64 = 664;
			test.str = "message";
			test.doub = 11.f;
			test.flo = 11.f;
			test.fi32 = 12345;
			test.fi64 = 123456;
			test.vec.push_back(123);
			test.mapp[1] = 1;
			test.mapp[2] = 1;
			test.mapp[3] = 1;
			test.mapp[4] = 1;
			test.mapp[5] = 1;
			test.mapp[6] = 1;
			test.mapp[7] = 1;
			test.mapp[8] = 1;
			test.mapp[9] = 1;
			test.mapp[10] = 1;
			test.rig.tt = 12;
			test.ttte = Test::Hello;
		}
	});
	unsigned char data[1000];
	test("编码", run_times, [&data](size_t t)->void {
		size_t size = 0;
		for (size_t i = 0; i < t; i++) {
			Test test;
			test.boo = true;
			test.int32 = 32;
			test.int64 = 641;
			test.sint32 = 232;
			test.sint64 = 264;
			test.uint32 = 632;
			test.uint64 = 664;
			test.str = "message";
			test.doub = 11.f;
			test.flo = 11.f;
			test.fi32 = 12345;
			test.fi64 = 123456;
			test.vec.push_back(123);
			test.mapp[1] = 1;
			test.mapp[2] = 1;
			test.mapp[3] = 1;
			test.mapp[4] = 1;
			test.mapp[5] = 1;
			test.mapp[6] = 1;
			test.mapp[7] = 1;
			test.mapp[8] = 1;
			test.mapp[9] = 1;
			test.mapp[10] = 1;
			test.ttte = Test::ttten::Hello;
			test.rig.tt = 12;
			size = test.serialize(data, 1000);
		}
		cout << "size" << size << " | ";
	});

	test("单例编码", run_times, [&data](size_t t)->void {
		size_t size = 0;
		for (size_t i = 0; i < t; i++) {
			Test &test = Test::instance();
			test.refresh();
			test.boo = true;
			test.int32 = 32;
			test.int64 = 641;
			test.sint32 = 232;
			test.sint64 = 264;
			test.uint32 = 632;
			test.uint64 = 664;
			test.str = "message";
			test.doub = 11.f;
			test.flo = 11.f;
			test.fi32 = 12345;
			test.fi64 = 123456;
			test.vec.push_back(123);
			test.mapp[1] = 1;
			test.mapp[2] = 1;
			test.mapp[3] = 1;
			test.mapp[4] = 1;
			test.mapp[5] = 1;
			test.mapp[6] = 1;
			test.mapp[7] = 1;
			test.mapp[8] = 1;
			test.mapp[9] = 1;
			test.mapp[10] = 1;
			test.ttte = Test::ttten::Hello;
			test.rig.tt = 12;
			size = test.serialize(data, 1000);
		}
		cout << "size" << size << " | ";
	});


	test("解码", run_times, [&data](size_t t)->void {
		size_t size;
		for (size_t i = 0; i < t; i++) {
			Test test;
			size = test.unserialize(data, 1000);
		}
		cout << "size" << size << " | ";
	});

	test("单例解码", run_times, [&data](size_t t)->void {
		size_t size;
		for (size_t i = 0; i < t; i++) {
			Test &test = Test::instance();
			test.refresh();
			size = test.unserialize(data, 1000);
		}
		cout << "size" << size << " | ";
	});

	test("简单编码", run_times, [&data](size_t t)->void {
		size_t size = 0;
		for (size_t i = 0; i < t; i++) {
			Simple test;
			test.boo = true;
			test.int32 = 32;
			test.int64 = 641;
			test.sint32 = 232;
			test.sint64 = 264;
			test.uint32 = 632;
			test.uint64 = 664;
			test.str = "message";
			test.doub = 11.f;
			test.flo = 11.f;
			test.fi32 = 12345;
			test.fi64 = 123456;
			test.rig.tt = 12;
			size = test.serialize(data, 1000);
		}
		cout << "size" << size << " | ";
	});
	cout << endl;
}
#endif

int main() {
#ifdef GENERATE_CODE
	collector::get_instance().generate_csharp("msg");
#else
	test_fast(10000);
	test_fast(100000);
	test_fast(1000000);
	test_fast(10000000);
#endif
}