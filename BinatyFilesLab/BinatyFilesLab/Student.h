#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::fstream;

class student {
public:
	int ID;
	char firstName[16];
	char lastName[16];
	char fatherName[16];
	char dateOfBirth[11];
	int grades[4]; 

	double averageScore = 0;

	void calculateAverageScore() {
		for (int i = 0; i < 4; ++i) {
			averageScore += grades[i];
		}
		averageScore /=  4;
	}
//Чтение и запись в бинарный файл
	bool ReadFromBin(fstream& in) {
		in.read((char*)&(*this), sizeof *this);
		return in.eof();
	}

	bool WriteFromBin(fstream& out) {
		if (!out) return 0;
		out.write((char*)&(*this), sizeof *this);
		return 1;
	}

	friend fstream& operator >> (fstream& in, student& countValue) {
		in >> countValue.ID >> countValue.lastName >> countValue.firstName >> countValue.fatherName >> countValue.dateOfBirth
			>> countValue.grades[0] >> countValue.grades[1] >> countValue.grades[2] >> countValue.grades[3];
		return in;
	}

	friend std::ostream& operator << (std::ostream& out, student& countValue) {
		out << countValue.ID << " " << countValue.lastName << " " << countValue.firstName << " " << countValue.fatherName << " " << countValue.dateOfBirth << 
		" "	<< countValue.grades[0] << " " << countValue.grades[1] << " " << countValue.grades[2] << " " << countValue.grades[3];
		return out;
	}

	friend fstream& operator << (fstream& out, student& countValue) {
		out << countValue.ID << " " << countValue.lastName << " " << countValue.firstName << " " << countValue.fatherName << " " << countValue.dateOfBirth <<
			" " << countValue.grades[0] << " " << countValue.grades[1] << " " << countValue.grades[2] << " " << countValue.grades[3];
		return out;
	}

};
