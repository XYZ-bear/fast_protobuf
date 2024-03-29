// general.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	ofstream f1("serializer.h");
	if (!f1)return 0;
	f1 << "#pragma once" << endl;

	f1 << endl;
	f1<< "#define DEFINE_ALL_PRE_SERIALIZE()\\"<<endl;
	size_t max = 256;
	for (int i = 1; i <= max; i++) {
		f1 << "inline void serialize_" + to_string(i) + "() {};";
		if (i % 4 == 0)
			f1 << "\\" << endl;
	}

	f1 << endl;
	f1 << "#define DEFINE_ALL_PRE_UNSERIALIZE()\\" << endl;
	for (int i = 1; i <= max; i++) {
		f1 << "inline void unserialize_" + to_string(i) + "() {};";
		if (i % 4 == 0)
			f1 << "\\" << endl;
	}

	f1 << endl;
	f1 << "#define IMPL_SERIALIZE(entity)\\" << endl;
	for (int i = 1; i <= max; i++) {
		f1 << "entity->serialize_" + to_string(i) + "();";
		if (i % 4 == 0)
			f1 << "\\" << endl;
	}

	f1 << endl;
	f1 << "#define IMPL_UNSERIALIZE(entity)\\" << endl;
	for (int i = 1; i <= max; i++) {
		f1 << "entity->unserialize_" + to_string(i) + "();";
		if (i % 4 == 0)
			f1 << "\\" << endl;
	}

	f1 << endl;
	f1 << "#define DEFINE_ALL_OPERATER()\\" << endl;
	for (int i = 1; i <= max; i++) {
		f1 << "inline void operater_" + to_string(i) + "(uint8_t o) {};";
		if (i % 4 == 0)
			f1 << "\\" << endl;

	}
	f1 << endl;
	f1 << "#define IMPL_OPERATER(entity,o)\\" << endl;
	for (int i = 1; i <= max; i++) {
		f1 << "entity->operater_" + to_string(i) + "(o);";
		if (i % 4 == 0)
			f1 << "\\" << endl;
	}
	f1 << ";" << endl;
    return 0;
}

