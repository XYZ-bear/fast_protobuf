// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "message.h"
using namespace std;

//#define KK(defin) defin+="123"
//
//#define SG(T,name) void set_##name(){}
//
//void set(string a) {
//	cout << a << endl;
//}
//
//class pb_base_field {
//protected:
//	size_t type;
//	void *pointer;
//};
//
//template<class T>
//class pb_field:public pb_base_field {
//public:
//	T val;
//	SG(T, password);
//	pb_field() {
//		type = typeid(T).hash_code();
//		pointer = &val;
//	}
//};
//
//class pb {
//public:
//	vector<pb_base_field*> list;// { new pb_field<int>(), new pb_field<string>() };
//	pb() {
//		list.push_back()
//	}
//};

void se(char *a) {
	a++;
}

int main()
{
	char *as=new char;
	se(as);
	//vector<float> a{ 1.1 };
	//vector<int> *b = reinterpret_cast<vector<int>*>(&a);
	//vector<float> *c = (vector<float>*)b;

	//int fff = 0;
	//fff++;

	

	//login2 a;
	rigist ri;
	ri.set_tt(12);
	//a.set_i1(-4);
	//a.set_thh(-1222222);
	//a.add_kkkk(1, 2);
	//a.add_vvv(ri);
	////a.add_vvv(ri);
	////a.set_str("fuck you bitch");
	//a.set_ttt(ri);
	//cout << a.get_i1() << endl;
	//cout << a.get_thh() << endl;
	//cout << a.get_kkkk(1) << endl;
	//cout << a.get_vvv()[0].get_tt() << endl;
	//cout << a.get_str() << endl;
	//cout << a.get_ttt().get_tt() << endl;
	//cout << a.size() << endl << endl;

	//clock_t startTime, endTime;
	//unsigned char data[1000];
	//size_t size=0;
	//int max = 1000000;
	//startTime = clock();//计时开始
	//for (int i = 0; i < max; i++) {
	//	size = a.serialize_with_tag_(data, 1000);
	//}
	//endTime = clock();
	//cout << endl << "se size:" << size << endl;
	//cout << endTime - startTime << endl;
	//

	//startTime = clock();//计时开始
	//
	//login2 t2;
	//for (int i = 0; i < max; i++) {
	//	size = t2.unserialize_with_tag_(data, size);
	//}
	//endTime = clock();
	//cout << endl << "unse size:" << size << endl;
	//cout << endTime - startTime << endl;


	//cout << t2.get_i1() << endl;
	//cout << t2.get_thh() << endl;
	//cout << t2.get_kkkk(1) << endl;
	//cout << t2.get_vvv()[0].get_tt() << endl;
	//cout << t2.get_str() << endl;
	//cout << t2.get_ttt().get_tt() << endl;

	//int tag = 10;
	///*tag |= 0x08;
	//tag |= 2;*/
	//cout << tag << endl;
	//tag << 4;
	//cout << tag << endl;


	Test test;
	test.set_boo(true);
	test.set_int32(32);
	test.set_int64(641);
	test.set_sint32(232);
	test.set_sint64(264);
	test.set_uint32(632);
	test.set_uint64(664);
	test.set_str("message");
	test.set_doub(11.f);
	test.set_flo(11.f);
	test.set_rig(ri);
	test.set_fix32(2532);
	test.set_fix64(2564);
	test.add_mapp(1, 2);
	int kk = 123;
	test.add_vec(kk);


	clock_t startTime, endTime;
	unsigned char data[1000];
	size_t size = 0;
	int max = 1000000;
	startTime = clock();//计时开始
	for (int i = 0; i < max; i++) {
		size = test.serialize(data, 1000);
	}
	endTime = clock();
	cout << endl << "se size:" << size << endl;
	cout << endTime - startTime << endl;


	startTime = clock();//计时开始

	Test t2;
	for (int i = 0; i < max; i++) {
		size = t2.unserialize(data, size);
	}
	endTime = clock();
	cout << endl << "unse size:" << size << endl;
	cout << endTime - startTime << endl;

	cout << t2.get_int32() << endl; 
	cout << t2.get_str() << endl;
	cout << t2.get_fix64() << endl;



	Test2 test2;
	test2.set_tt(123);
	test2.set_uint64(12345);
	cout << test2.get_tt() << endl;
	cout << test2.get_uint64() << endl;

	cout << test2.serialize(data, 1000) << endl;
	Test2 test3;
	cout << test3.unserialize(data, 1000) << endl;
	cout << test3.get_tt() << endl;
	cout << test3.get_uint64() << endl;

	//cout << t2.get_size() << endl << endl;

	//int countt = 100000000;
	//funct fkmk;
	//startTime = clock();//计时开始
	//for (int i = 0; i < countt; i++) {
	//	fkmk.ccm();
	//}
	//endTime = clock();
	//cout << endTime - startTime << endl;

	//startTime = clock();//计时开始
	//int a = 0;
	//for (int i = 0; i < countt; i++) {
	//	fkmk.count();
	//}
	//endTime = clock();
	//cout << endTime - startTime << endl;

	//startTime = clock();//计时开始
	//for (int i = 0; i < countt; i++) {
	//	fkmk.count2();
	//}
	//endTime = clock();
	//cout << endTime - startTime << endl;

	//void (funct::*ff)() = &funct::ccm;
	//startTime = clock();//计时开始
	//for (int i = 0; i < countt; i++) {
	//	(fkmk.*ff)();
	//}
	//endTime = clock();
	//cout << endTime - startTime << endl;
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
