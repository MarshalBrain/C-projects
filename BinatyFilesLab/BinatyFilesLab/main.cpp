#include <Windows.h>
#include <iostream>
#include <algorithm>
#include "Student.h"


string LANGUAGE = "RU";

void chooseLanguage();

void ListOfStudentsWithMark4();

void ListOfStudentsWithMarks9and10();

void ListOfStudentsWithTheSameDatesOfBirth();

void ListOfStudentsWithTheSameMarks();

void ListOfStudentsWithTheBetterMarks();

void ChangeThePositionOfStudentsWithBestMarksAndWorstMarks();

void SortStudents();

void DeleteStudents();

void PrintBinFile();

void MENU();

void readFile();

void writeFile();

void putToTheAnswerScreen(vector<student>&);

vector<student> Students;

int main() {
	setlocale(LC_ALL, "RUS");
//	setlocale(LC_CTYPE, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	readFile();

	chooseLanguage();

	MENU();
	
	writeFile();
	
	return 0;
}

void readFile() {
	fstream intxt("input.txt", std::ios::in);
	fstream outbin("input.bin", std::ios::binary | std::ios::out);
	student val;

	while (intxt >> val) {
		outbin.write((char*)&val, sizeof(val));
	}

	intxt.close();
	outbin.close();
	
	fstream inbin("input.bin", std::ios::binary | std::ios::in);
	student tempStud;

	while (!tempStud.ReadFromBin(inbin)) {
		Students.push_back(tempStud);
	}


	for (int i = 0; i < (int)Students.size(); ++i) {
		Students[i].calculateAverageScore();
	}

	inbin.close();
}

void writeFile() {
	fstream outbin("output.bin", std::ios::binary | std::ios::out);
	for (int i = 0; i < (int)Students.size(); ++i) {
		outbin.write((char*)&Students[i], sizeof(Students[i]));
	}
	outbin.close();

	fstream inbin("output.bin", std::ios::binary | std::ios::in);
	fstream output("output.txt");
	student tempStud;

	while (inbin.read((char*)&tempStud, sizeof tempStud)){
		output << tempStud << "\n";
	}

	inbin.close();
	output.close();
}

void chooseLanguage() {
	std::cout << "Choose your language\nВыберите ваш язык\n1.RU\n2.EN\n";
	char userAnswer;
	std::cin >> userAnswer;
	if (userAnswer == '1') LANGUAGE = "RU";
	if (userAnswer == '2') LANGUAGE = "EN";
}

void MENU() {
	system("CLS");
	if (LANGUAGE == "RU") std::cout << "1.Cписок студентов, у которых хотя бы одна оценка равна 4;\n2.Cписок студентов сдавших сессию на 9 и 10;\n3.Cписок студентов, дата рождения у которых совпадает;\n4.Cписок студентов, у каждого из которых оценки по всем экзаменам совпадают;\n5.Cписок студентов с наибольшим средним баллом;\n6.Поменять местами записи с минимальным и максимальным средним баллом студента;\n7.Упорядочить по среднему балу студента;\n8.Удалить все записи, у которых имя студента совпадает с введенным с клавиатуры;\n9.Вывести список студентов из выходного бинарного файла;\n0.Выйти;\n";
	if (LANGUAGE == "EN") std::cout << "1.List of students with mark 4;\n2.List of students, that passed exam with marks 9 and 10;\n3.List of students with the same dates of birth;\n4.List of students with the same marks for all exams;\n5.List of students with the best average score;\n6.Swap student with average score and student with worst average score;\n7.Sort students by average score;\n8.Delete students from list whose names were entered from the keyboard;\n9.Print list of students from the binary output file;\n0.Quit;\n";
	int number;
	std::cin >> number;
	system("CLS");
	if (number == 1) ListOfStudentsWithMark4();
	if (number == 2) ListOfStudentsWithMarks9and10();
	if (number == 3) ListOfStudentsWithTheSameDatesOfBirth();
	if (number == 4) ListOfStudentsWithTheSameMarks();
	if (number == 5) ListOfStudentsWithTheBetterMarks();
	if (number == 6) ChangeThePositionOfStudentsWithBestMarksAndWorstMarks();
	if (number == 7) SortStudents();
	if (number == 8) DeleteStudents();
	if (number == 9) PrintBinFile();
	if (number == 0) return;
}

void PrintBinFile() {
	vector<student> answer = Students;
	putToTheAnswerScreen(answer);
}

void putToTheAnswerScreen(vector<student>& answer) {
	
	if (answer.size()) {
		for (int i = 0; i < (int)answer.size(); ++i) {
			std::cout << i+1 << ". " << answer[i] << std::endl;
		}
	}
	else {
		if (LANGUAGE == "RU") std::cout << "Список пуст:(\n";
		if (LANGUAGE == "EN") std::cout << "List is empty:(\n";
	}

	if (LANGUAGE == "RU") std::cout << "Вернуться в меню?\nД\\Н ";
	if (LANGUAGE == "EN") std::cout << "Return to the menu?\nY\\N ";
	char userAnswer;
	std::cin >> userAnswer;
	system("CLS");
	if (LANGUAGE == "RU" && (userAnswer == 'Д' || userAnswer == 'д' || userAnswer == 'l' || userAnswer == 'L')) MENU();
	if (LANGUAGE == "EN" && (userAnswer == 'Y' || userAnswer == 'y' || userAnswer == 'н' || userAnswer == 'Н')) MENU();
	else return;
}

void ListOfStudentsWithMark4() {
	vector<student> answer;
	for (int i = 0; i < (int)Students.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			if (Students[i].grades[j] == 4) {
				answer.push_back(Students[i]);
				break;
			}
		}
	}
	putToTheAnswerScreen(answer);
}

void ListOfStudentsWithMarks9and10() {
	vector<student> answer;
	for (int i = 0; i < (int)Students.size(); ++i) {
		bool isBotan = 1;
		for (int j = 0; j < 4; ++j) {
			if (Students[i].grades[j] < 9) isBotan = 0;
		}
		if (isBotan) answer.push_back(Students[i]);
	}
	putToTheAnswerScreen(answer);
}

void ListOfStudentsWithTheSameDatesOfBirth() {
	vector<student> answer;
	for (int i = 0; i < (int)Students.size(); ++i) {
		for (int j = i + 1; j < (int)Students.size(); ++j) {
			bool isTheSame = 1;
			for (int k = 0; k < 10; ++k) {
				if (Students[i].dateOfBirth[k] != Students[j].dateOfBirth[k]) isTheSame = 0;
			}
			if (isTheSame) {
				answer.push_back(Students[i]), answer.push_back(Students[j]);
			}
		}
	}
	putToTheAnswerScreen(answer);
}

void ListOfStudentsWithTheSameMarks() {
	vector<student> answer;
	for (int i = 0; i < (int)Students.size(); ++i) {
		bool isTheSameMarks = 1;
		for (int j = 1; j < 4; ++j) {
			if (Students[i].grades[j] != Students[i].grades[j - 1]) {
				isTheSameMarks = 0;
			}
		}
		if (isTheSameMarks) answer.push_back(Students[i]);
	}
	putToTheAnswerScreen(answer);
}

void ListOfStudentsWithTheBetterMarks() {
	vector<student> answer;
	double theBestAverageScore = 4.0;

	for (int i = 0; i < (int)Students.size(); ++i) {
		theBestAverageScore = max(theBestAverageScore, Students[i].averageScore);
	}

	for (int i = 0; i < (int)Students.size(); ++i) {
		if (abs(Students[i].averageScore - theBestAverageScore) < 0.00000000001) answer.push_back(Students[i]);
	}

	putToTheAnswerScreen(answer);
}

void ChangeThePositionOfStudentsWithBestMarksAndWorstMarks() {
	double minAverageScore = 10, maxAverageScore = 0;
	int iterOnMin, iterOnMax;
	for (int i = 0; i < (int)Students.size(); ++i) {
		Students[i].calculateAverageScore();
		minAverageScore = min(minAverageScore, Students[i].averageScore);
		maxAverageScore = max(maxAverageScore, Students[i].averageScore);
	}

	for (int i = 0; i < (int)Students.size(); ++i) {
		if (minAverageScore == Students[i].averageScore) {
			iterOnMin = i;
		}
		if (maxAverageScore == Students[i].averageScore) {
			iterOnMax = i;
		}
	}
	std::swap(Students[iterOnMax], Students[iterOnMin]);

	if (LANGUAGE == "RU") std::cout << "Готово. Вернуться в меню?(Д\\Н)\n";
	if (LANGUAGE == "EN") std::cout << "Done. Return to the menu?(Y\\N)\n";
	char userAnswer;
	std::cin >> userAnswer;
	if (LANGUAGE == "RU" && (userAnswer == 'Д' || userAnswer == 'д' || userAnswer == 'l' || userAnswer == 'L')) MENU();
	if (LANGUAGE == "EN" && (userAnswer == 'Y' || userAnswer == 'y' || userAnswer == 'н' || userAnswer == 'Н')) MENU();
	else return;
}

void SortStudents() {
	std::sort(Students.begin(), Students.end(), [](student First, student Second) {
		return First.averageScore < Second.averageScore; });

	if (LANGUAGE == "RU") std::cout << "Готово. Вернуться в меню?(Д\\Н)\n";
	if (LANGUAGE == "EN") std::cout << "Done. Return to the menu?(Y\\N)\n";
	char userAnswer;
	std::cin >> userAnswer;
	if (LANGUAGE == "RU" && (userAnswer == 'Д' || userAnswer == 'д' || userAnswer == 'l' || userAnswer == 'L')) MENU();
	if (LANGUAGE == "EN" && (userAnswer == 'Y' || userAnswer == 'y' || userAnswer == 'н' || userAnswer == 'Н')) MENU();
	else return;
}

void DeleteStudents() {
	if (LANGUAGE == "RU") std::cout << "Введите имя:\n";
	if (LANGUAGE == "EN") std::cout << "Enter name:\n";
	char* Name = new char;
	std::cin >> Name;
	system("CLS");
	for (int i = 0; i < (int)Students.size(); ++i) {
		if (strcmp(Students[i].firstName, Name) == 0) {
			Students.erase(Students.begin()+i);
		}
	}
	if (LANGUAGE == "RU") std::cout << "Готово. Вернуться в меню?(Д\\Н)\n";
	if (LANGUAGE == "EN") std::cout << "Done. Return to the menu?(Y\\N)\n";
	char userAnswer;
	std::cin >> userAnswer;
	if (LANGUAGE == "RU" && (userAnswer == 'Д' || userAnswer == 'д' || userAnswer == 'l' || userAnswer == 'L')) MENU();
	if (LANGUAGE == "EN" && (userAnswer == 'Y' || userAnswer == 'y' || userAnswer == 'н' || userAnswer == 'Н')) MENU();
	else return;
}