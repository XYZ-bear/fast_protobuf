// proto.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include "message.h"
#include <ctime>
#include "module.h"
#include "login.h"

#define _CRT_SECURE_NO_WARNINGS

void test(string name,size_t t,function<void(size_t t)> f) {
	clock_t startTime, endTime;
	startTime = clock();
	f(t);
	endTime = clock();
	cout << name << "  |  " << t << "  |  " << endTime - startTime << "ms" << endl;
}

struct ttt
{
	ttt(uint32_t v):val(v) {
	}
	uint32_t val;
};
enum KK{
	ff
};
class TTT {
public:
	template<class T>
	size_t operator<<(vector<T> &v) {
		for (size_t i = 0; i < v.size(); i++)
			*this<<(v[i]);
		return 0;
	}
	size_t  operator<<(int v) {
		cout << v << endl;
		return 1;
	}

	template<class T>
	size_t tt(vector<T> &v) {
		for (size_t i = 0; i < v.size(); i++)
			tt(v[i]);
			//*this << (v[i]);
		return 0;
	}
	KK val;
	void en(int v) {
		tt(val);
	}

	void en2(int &v,int v2) {
		//*v = v2;
	}

	size_t  tt(int &v) {
		cout << v << endl;
		return 1;
	}
	template<class T>
	void tt(T t) {

	}

};

enum TTEN
{
	TTENKK
};

void sf(TTEN v) {}

//template<class T>
//void typem(vector<T> *r, string &name);
//
//template<class T1,class T2>
//void typem(map<T1,T2> *r, string &name);
//
//void typem(int *r, string &name);
//
//template<class T>
//void typem(vector<T> *r, string &name) {
//	T *val = nullptr;
//	typem(val, name);
//	name = "vector<" + name + ">";
//}
//
//template<class T1, class T2>
//void typem(map<T1, T2> *r, string &name) {
//	T1 *key = nullptr;
//	T2 *val = nullptr;
//
//	typem(val, name);
//	name = "," + name + ">";
//	string key_type;
//	typem(key, key_type);
//	name = "map<" + key_type + name;
//}
//
//void typem(int *r, string &name) {
//	name += "int";
//}
enum fdsfs
{
	sjjj=100
};
int main() {

//	fixed32 ffkk=12;
//	ffkk = 12;
//	uint32_t res = ffkk;
//	fixed32 ffkk2 = ffkk;
//	float a;
//	if (ffkk2 == 12) {}
//	enum_base<TTEN> fs = TTENKK;
//	fs = TTENKK;
//	sf(fs);
//
//	//vector<int> v1;
//	//v1.push_back(1);
//	//vector<vector<int>> v2;
//	//v2.push_back(v1);
//	//vector<vector<vector<int>>> vv;
//	//vv.push_back(v2);
//	KK ll = ff;
//	TTT gt; gt.tt(ll);
//	////gt << vv;
//	//gt.tt(vv);
//	//return 0;
//	//for (int i = 0; i < 20; i++) {
#ifdef GENERATE_CODE
	fdsfs adg;
	fdsfs sfdf;
	auto &ins = collector::get_instance();
	//map<int,vector<vector<int>>> ak;
	//string name;
	//cout << cshrap_type_map::type(&ak) << endl;

	int a = 0;
	a++;
	ins.generate_csharp("msg");
#else


		size_t run_times = 1000000;
		test("构造与析构", run_times, [](size_t t)->void {
			for (int i = 0; i < t; i++) {
				Test test;
			}
		});
		test("赋值", run_times, [](size_t t)->void {
			for (int i = 0; i < t; i++) {
				Test test;
#ifdef USE_SET_GET
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
				test.set_fi32(12345);
				test.set_fi64(123456);
				test.add_vec(123);
				test.add_mapp(1, 1);
				test.get_rig().set_tt(12);
#else
				test.boo=true;
				test.int32=32;
				test.int64=641;
				test.sint32=232;
				test.sint64=264;
				test.uint32=632;
				test.uint64=664;
				test.str="message";
				test.doub=11.f;
				test.flo=11.f;
				test.fi32=12345;
				test.fi64=123456;
				test.vec.push_back(123);
				test.mapp[1]= 1;
				test.rig.tt=12;
				test.ttte = Test::Hello;
#endif // USE_SET_GET


			}
		});
		unsigned char data[1000];
		test("编码", run_times, [&data](size_t t)->void {
			size_t size=0;
			for (int i = 0; i < t; i++) {
				Test test;
				//Test &test= Test::instance();
				//test.refresh(&test);
#ifdef USE_SET_GET
				test.set_boo(true);
				test.set_int32(32);
				test.set_int64(641);
				test.set_sint32(232);
				test.set_sint64(264);
				test.set_uint32(632);
				test.set_uint64(664);
				test.set_str("message");
				test.set_doub(-11.1);
				test.set_flo(11.2f);
				test.set_fi32(12345);
				test.set_fi64(123456);
				test.add_vec(123);
				test.get_rig().set_tt(12);
				test.add_mapp(1, 1);
				test.add_mapp(2, 1);
				test.add_mapp(3, 1);
				test.add_mapp(4, 1);
				test.add_mapp(5, 1);
				test.add_mapp(6, 1);
				test.add_mapp(7, 1);
				test.add_mapp(8, 1);
				test.add_mapp(9, 1);
				test.add_mapp(10, 1);
				test.set_ttte(Test::ttten::Hello);
#else
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
				test.ennene = Test::ttten::Bitch;

				test.rig.tt = 12;
#endif // USE_SET_GET

				size=SERIALISE(test, data, 1000);
			}
			cout << "size" << size <<" | ";
		});
		test("解码", run_times, [&data](size_t t)->void {
			size_t size;
			for (int i = 0; i < t; i++) {
				Test test;
				//Test &test = Test::instance();
				//test.refresh(&test);
				size = UNSERIALISE(test, data, 1000);
			}
			cout << "size" << size << " | ";
		});
		test("取值", run_times, [&data](size_t t)->void {
			Test test;
			UNSERIALISE(test, data, 1000);
			
			Test tt = test;
		});
		test("继承", run_times, [](size_t t)->void {
			//unsigned char data[1000];
			//Test3 test;
			//test.set_str("kkk");
			//test.set_str2("222");
			//SERIALISE(test, data, 1000);

			////for (int i = 0; i < t; i++) {
			//	Test3 tts;
			//	UNSERIALISE(tts, data, 1000);
			//	tts.get_boo();
			//}
		});

		test("嵌套", run_times, [](size_t t)->void {
			//unsigned char data[1000];
			//Test4 t4;
			//t4.tt[1].push_back(1);
			//SERIALISE(t4, data, 1000);

			//Test4 tts;
			//UNSERIALISE(tts, data, 1000);

			//Test5 t5;
			//t5.intt = 12;
			//t5.vvc.push_back(12);
			//t5.mmp[1] = 1;

			//SERIALISE(t5, data, 1000);

			//Test5 tts5;
			//UNSERIALISE(tts5, data, 1000);
			//t5.fix = 12;
			//tts.get_tt();
		});
#endif // GENERATE_CODE
	//}
//		using tttt=int;
//		
//		//vector<int> vec;
//		//int::
//		//vector<int>::value_type
//		
//
//
//	//cout << t2.get_int32() << endl;
//	//cout << t2.get_str() << endl;
//	//cout << t2.get_vec()[0] << endl;
//	////cout << t2.get_fix64() << endl;
//	//cout << t2.get_fi32() << endl;
//	//cout << t2.get_fi64() << endl;
//
//	//Test2 test2;
//	//test2.set_tt(123);
//	//test2.set_uint64(12345);
//	//cout << test2.get_tt() << endl;
//	//cout << test2.get_uint64() << endl;
//
//	//cout << test2.serialize(data, 1000) << endl;
//	//Test2 test3;
//	//cout << test3.unserialize(data, 1000) << endl;
//	//cout << test3.get_tt() << endl;
//	//cout << test3.get_uint64() << endl;
//
//	//proto_manager::get_instance().impl(1, data, 1000);
//	//funct fkmk;
//	//startTime = clock();//计时开始
//	//for (int i = 0; i < 100000; i++) {
//	//	fkmk.ccm(1);
//	//	fkmk.ccm(1.22f);
//	//}
//	//endTime = clock();
//	//cout << endTime - startTime << endl;
//
//	//startTime = clock();//计时开始
//	//for (int i = 0; i < 100000; i++) {
//	//	fkmk.fj(1);
//	//	fkmk.fj(2);
//	//}
//	//endTime = clock();
//	//cout << endTime - startTime << endl;
//
//	//cout << t2.get_i1() << endl;
//	//cout << t2.get_thh() << endl;
//	//cout << t2.get_size() << endl;
//	//cout << is_signed<login2>() << endl;
//	//unsigned char* next = data;
//	//int ab = -1;
//	//uint32_pack(zigZag_encode32(ab), next);
//	//uint32_t re = 0;
//	////varint_decode_uint32(data, &re);
//	//re = parse_uint32(1, data);
//	//int tf = zigZag_decode32(re);
//#define Bit_bit_1 0x80
//#define Bit_bit_2 0x40
//#define Bit_bit_3 0x20
//#define Bit_bit_4 0x10
//#define Bit_bit_5 0x08
//#define Bit_bit_6 0x04
//#define Bit_bit_7 0x02
//#define Bit_bit_8 0x01
//
//	char ids = 3;
//	cout << (ids & Bit_bit_8) << endl;
//	//ids |= Bit_bit_1;
//	ids |= Bit_bit_2;
//	cout << (int)ids << endl;
//
//
//
//
//
}

//int main()
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