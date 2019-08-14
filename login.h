#pragma once
#include "module.h"
#include "message.h"

class login :public module<login> {
	Rigist(passs, 1, login2, 1);
	Rigist(get_rigist, 2, rigist, 2);
};

void login::passs(login2 &val) {
	cout << "login modul" << endl;
	cout << val.get_i1() << endl;
	cout << val.get_thh() << endl;
	//cout << a.get_kkkk(1) << endl;
	//cout << a.get_vvv()[0].get_tt() << endl;
	cout << val.get_str() << endl;
	cout << val.get_ttt().get_tt() << endl;
	cout << val.get_dou() << endl;
	cout << (int)val.get_ev() << endl;
	cout << val.size() << endl << endl;
	cout << "endl" << endl;
}

void login::get_rigist(rigist &val) {
	cout << "login modul" << endl;
	cout << val.get_tt() << endl;
	cout << "endl" << endl;
};
