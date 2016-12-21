// BinatyFilesLab.cpp: определяет точку входа для консольного приложения.
//
#include "Student.h"

int mainR()
{
	fstream in("input.txt");
	fstream out("input.bin", std::ios::binary | std::ios::out);
	student val;

	while (in >> val) {
		out.write((char*)&val, sizeof(val)); 
	}

	in.close();
	out.close();
    return 0;
}

