// BinatyFilesLab.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "Student.h"

int mainW()
{
	fstream in("output.bin", std::ios::binary | std::ios::in);
	fstream out("output.txt");
	student val;

	while (in.read((char*)&val, sizeof(val))) {
		out << val << "\n";
	}

	in.close();
	out.close();
	return 0;
}

