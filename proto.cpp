// proto.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include "message.h"
#include <ctime>
//#include "proto_base3.h"
#include <typeinfo>
#define _CRT_SECURE_NO_WARNINGS
//struct field_info {
//	void *val_address = nullptr;
//	function<void*()> new_one_func_;
//	//char flag;//r->l:is_set | is_vector | is_map | is_msg | 1byte | 2byte | 4byte | 8byte
//};
//struct vector_field_info : public field_info {
//	void *defalt_value;
//	vector_field_info(function<void*()> back) {
//		new_one_func_ = back;
//	}
//};
//struct map_field_info : public field_info {
//	int mf;
//};
//
//field_info *inf;
//
//template<class T>
//void set_t() {
//	function<void*()> new_one = []()->void* {
//		return (void*)(new T);
//	};
//	vector_field_info *ni = new vector_field_info(new_one);
//	inf = ni;
//}

class cpppy {
public:
	int a;
	cpppy() {
		cout << "build" << endl;
		cout << &a << endl;
	}
	cpppy(const cpppy& c) {
		//*this = c;
		cout << "copy build" << endl;
		cout << &a << endl;
	}
	void outa() {
		cout << &a << endl;
	}
	cpppy& operator=(const cpppy &c) {
		cout << "==" << endl;
		return *this;
	}
};

template<class T,class Con=T>
void show_type() {
	//cout << typeid(T).name() << endl;
	//using type = typename std::decay<typename vector<vector<int>>::value_type>::type;
	//using type = typename std::decay<typename T::value_type>::type;
	//show_type<type::value_type, type>();
	//if (0)
	//	T::value_type;

}
int main() {
	login2 a;
	rigist ri;
	ri.set_tt(12);
	a.set_i1(-4);
	a.set_thh(-1222222);
	a.add_kkkk(1, 2);
	a.add_vvv(ri);
	a.set_str("fuck you bitch");
	a.set_ttt(ri);
	cout << a.get_i1() << endl;
	cout << a.get_thh() << endl;
	cout << a.get_kkkk(1) << endl;
	cout << a.get_vvv()[0].get_tt() << endl;
	cout << a.get_str() << endl;
	cout << a.get_ttt().get_tt() << endl;
	cout << a.get_size() << endl << endl;

	clock_t startTime, endTime;
	unsigned char data[1000];
	size_t size;
	int max = 1000000;
	startTime = clock();//计时开始
	for (int i = 0; i < max; i++) {
		size = a.serialize(data, 1000);
	}
	endTime= clock();
	cout << endTime - startTime << endl;

	startTime = clock();//计时开始
	login2 t2;
	for (int i = 0; i < max; i++) {
		t2.unserialize(data, size);
	}
	endTime = clock();
	cout << endTime - startTime << endl;


	cout << t2.get_i1() << endl;
	cout << t2.get_thh() << endl;
	cout << t2.get_kkkk(1) << endl;
	cout << t2.get_vvv()[0].get_tt() << endl;
	cout << t2.get_str() << endl;
	cout << t2.get_ttt().get_tt() << endl;
	cout << t2.get_size() << endl << endl;

	funct fkmk;
	startTime = clock();//计时开始
	for (int i = 0; i < 100000; i++) {
		fkmk.ccm();
	}
	endTime = clock();
	cout << endTime - startTime << endl;

	startTime = clock();//计时开始
	for (int i = 0; i < 100000; i++) {
		fkmk.count();
	}
	endTime = clock();
	cout << endTime - startTime << endl;



	//cout << t2.get_i1() << endl;
	//cout << t2.get_thh() << endl;
	//cout << t2.get_size() << endl;
	//cout << is_signed<login2>() << endl;
	//unsigned char* next = data;
	//int ab = -1;
	//uint32_pack(zigZag_encode32(ab), next);
	//uint32_t re = 0;
	////varint_decode_uint32(data, &re);
	//re = parse_uint32(1, data);
	//int tf = zigZag_decode32(re);

}

////int main()
//{
//	//cpppy p1;
//	//p1.a = 123;
//	//cpppy p2;
//	//p2 = p1;
//	//p1.outa();
//	//p2.outa();
//	//set_t<int>();
//	//cout << inf->new_one_func_() << endl;
//
//	//login base;
//	//base.set_dex(12);
//	////base.set_dex(13);
//	//base.set_df(1.12);
//	////base.set_paa(tt{1,206,"abv"});
//	//base.set_str("eeff");
//	//cout << base.get_size() << endl;
//	//rigist ri;
//	//ri.set_tt(123);
//	//base.set_ttt(ri);
//	//cout << base.get_dex() << endl;
//	//cout << base.get_df() << endl;
//	////cout << base.get_paa().a << endl;
//	//cout << base.get_str() << endl;
//	//rigist tts = base.get_ttt();
//	//cout << base.get_ttt().get_tt() << endl;
//	
//
//	//login base2;
//	//base2.unerialize(base.get_buff(),base.get_size());
//	//cout << base2.get_dex() << endl;
//	//cout << base2.get_paa().a << endl;
//	//cout << base2.get_ttt().get_tt() << endl;
//
//	//unsigned char vec[100];
//	//unsigned char *next=varint_encode_uint32(300,vec);
//	//varint_encode_uint32(zigZag_encode32(-1000), next);
//	//unsigned int tttt;
//	//const unsigned char *nex=varint_decode_uint32(vec, &tttt);
//	//int ttk = zigZag_decode32(tttt);
//	//varint_decode_uint32(nex, &tttt);
//	//ttk = zigZag_decode32(tttt);
//
//	//map<int, int> mpp;
//	//cout << typeid(mpp).raw_name() << endl;
//	//tt tf{ 1,120 };
//	//uint32_t kk = 300;
//	//memcpy(vec, &kk, sizeof(uint32_t));
//
//	//short a = 0;
//	//short i = 2;
//	//short pos = 30;
//	//a = (pos << 3) | i;
//	//cout << a << endl;
//	//cout << (a >> 3) << endl;
//	//cout << (a^(30<<3)) << endl;
//	//
//	//cout << (i >> 1) << endl;
//	//cout << (i >> 2) << endl;
//	//cout << (i >> 3) << endl;
//	//cout << typeid(int).raw_name();
//
//	//char fsd[12];
//	//double kk = *(double*)fsd;
//	
//	//string kk = "afsdddddddddddddddddddddooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooddddddddd";
//	//cout << sizeof(kk) << endl;
//	//int a;
//	//memcpy(a)
//	//for (auto &filed : base.filed) {
//	//	cout << filed << endl;
//	//}
//	{}
//	//cout << sizeof(login2::field_info) << endl;
//	login2 base;
//	rigist ri;
//	//ri.set_tt(-123);
//	//base.set_ttt(ri);
//	//cout << base.get_ttt().get_tt() << endl;
//
//	//ri.set_tt(456);
//	//base.get_vvv().push_back(ri);
//	//cout << base.get_vvv()[0].get_tt() << endl;
//
//	//ri.set_tt(-789);
//	//base.add_vvv2(ri);
//	////base.get_vvv2().push_back(ri);
//	//cout << base.get_vvv2()[0].get_tt() << endl;
//
//	//base.set_str("hello");
//	//cout << base.get_str() << endl;
//
//	//base.add_kkkk(1, 1);
//	//cout << base.get_kkkk(1) << endl;
//
//	//base.set_en(TTTTFFK);
//	//cout << base.get_en() << endl;
//
//
//	//unsigned char data[100];
//	//size_t size = base.serialize(data, 1000);
//	//cout << "size1:"<<size << endl;
//	//cout << "size2:" << base.get_size() << endl;
//
//
//	//login2 lo;
//	//lo.unserialize(data, size);
//	//cout << lo.get_ttt().get_tt() << endl;
//	//cout << lo.get_vvv()[0].get_tt() << endl;
//	//cout << lo.get_vvv2()[0].get_tt() << endl;
//	//cout << lo.get_str() << endl;
//	//cout << lo.get_kkkk(1) << endl;
//	//cout << lo.get_en() << endl;
//
//
////	base.set_dex(12);
////	base.set_df(1.12);
////	//base.set_paa(tt{1,206,"abv"});
////	base.set_str("eeff");
////	rigist ri;
////	//ri.set_tt(13);
////	rigist ri2 = ri;;
//////	ri.set_tt(123);
////	base.set_ttt(ri);
////	//ri.set_tt(456);
////	base.get_vvv().push_back(ri);
////	ri.set_tt(456);
////	base.get_vvv2().push_back(ri);
////	//cout << base.get_size() << endl;
////	cout << base.get_dex() << endl;
////	cout << base.get_df() << endl;
////	//cout << base.get_paa().a << endl;
////	cout << base.get_str() << endl;
////    cout << base.get_ttt().get_tt() << endl;
////	cout << base.get_vvv()[0].get_tt() << endl;
////	cout << base.get_vvv2()[0].get_tt() << endl;
////
////
////
////	//proto_base *pb = (proto_base*)((void*)&base);
////	unsigned char data[1000];
////	size_t size = base.serialize(data, 1000);
////	cout << endl << "size" << size << endl << endl;
////
////	login2 t2;
////	t2.unserialize(data, size);
////	cout << t2.get_dex() << endl;
////	cout << t2.get_df() << endl;
////	//cout << t2.get_paa().a << endl;
////	cout << t2.get_str() << endl;
////	cout << t2.get_ttt().get_tt() << endl;
////	cout << t2.get_vvv()[0].get_tt() << endl;
////	cout << t2.get_vvv2()[0].get_tt() << endl;
//
//	vector<int> a;
//	vector<double> b;
//	cout << typeid(a).name() << endl;
//	cout << typeid(b).name() << endl;
//	cout << typeid(a).hash_code() << endl;
//	cout << typeid(b).hash_code() << endl;
//
//
//	cout << typeid(int).name() << endl;
//	using type = typename std::decay<typename vector<vector<int>>::value_type>::type;
//	cout << typeid(type).name() << endl;
//
//	//using type = typename std::decay<typename int::value_type>::type;
//	//cout << typeid(type).name() << endl;
//
//
//	vector<int> jj;
//	cout << jj.data() << endl;
//	map<int, int> mm;
//
//	char code=0x6;
//	code = code & 0x4;
//	cout << (int)(code) << endl;
//	cout << is_base_of<proto_base, int>() << endl;
//	cout << is_base_of <_Vector_alloc<_Vec_base_types<int, allocator<int>>>, vector<int>>() << endl;
//
//
//	//proto_base::vector_field_info vff;
//	//vff.value_type = proto_base::TYPE_1B;
//	//proto_base::field_info *ffffi = &vff;
//	//proto_base::vector_field_info *vf2 = (proto_base::vector_field_info*)ffffi;
//	//cout << vf2->value_type << endl;
//
//
//	show_type<int>();
//	/*cout << is_array<vector<int>>() << endl;*/
//
//	
//	//std::any abc;
//	//abc = 1;
//	//std::cout << abc.type().name() << ": " << std::any_cast<int>(abc) << '\n';
//	//abc = 3.14;
//	//std::cout << abc.type().name() << ": " << std::any_cast<double>(abc) << '\n';
//	////abc = ;
//	////std::cout << abc.type().name() << ": " << std::any_cast<bool>(abc) << '\n';
//
//	//int* i = std::any_cast<int>(&abc);
//	//vector<int> akk;
//	//abc = akk;
//	cout << is_arithmetic<string>() << endl; //是否可算术
//	cout << is_floating_point<double>() << endl;
//	cout << sizeof(double) << endl;
//	//cout << is_standard_layout<int>()::value << endl;
//	std::cout << typeid(vector<int>::value_type).name() << std::endl;
//	//cout << typeid(vector<vector<int>>).name() << endl;
//    return 0;
//}

//class Base
//{
//public:
//	//virtual void vvfunc() {}
//};
//
//class Derived : public Base {};
//
//using namespace std;
//
//int main()
//{
//	//Derived* pd = new Derived;
//	Derived pd;
//	Base pb = pd;
//
//	cout << typeid(pb).name() << endl;   // prints "class Base *"
//	//cout << typeid(*pb).name() << endl;  // prints "class Derived"
//	cout << typeid(pd).name() << endl;   // prints "class Derived *"
//	//cout << typeid(*pd).name() << endl;  // prints "class Derived"
//
//	//delete pd;
//}