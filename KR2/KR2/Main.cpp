#include "Human.h"
#include "Parent.h"
#include "Child.h"

#include <conio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

map <int, Human*> findParent;
map <int, int> childrenAmount;
vector <Human*> withBothParents;

enum State {EXIT, START, ERROR, F_INIT, C_INIT, PRINT_PARENTS, PRINT_CHILDREN, PRINT_PARENTS_WITH_MAX_CHILDREN,
	PRINT_CHILDREN_WITH_BOTH_PARENTS, MUM_DAD, GIRLS_BOYS, CLEAR};

void StartMenu(State& state) {
	system("cls");
	cout << "1 - Открыть файл для записи гостей.\n";
	cout << "2 - Открыть файл вывода.\n";
//	cout << "3 - Добавить гостя (в консоли).\n";
	cout << "3 - Вывести всех родителей.\n";
	cout << "4 - Вывести всех детей.\n";
	cout << "5 - Вывести родителей с максимальным количеством детей.\n";
	cout << "6 - Вывести детей, которые пришли с папой и мамой.\n";
	cout << "7 - Кого больше? (пап или мам).\n";
	cout << "8 - Кого больше? (мальчиков или девочек).\n";
	cout << "9 - Очистить список.\n";
	cout << "0 - Выйти.\n";
	char answer;
	answer = _getch();
	switch (answer) {
	case '1':
		state = F_INIT;
		break;
	case '2':
		system("output.txt");
		break;
	/*case '3':
		state = C_INIT;
		break;*/
	case '3':
		state = PRINT_PARENTS;
		break;
	case '4':
		state = PRINT_CHILDREN;
		break;
	case '5':
		state = PRINT_PARENTS_WITH_MAX_CHILDREN;
		break;
	case '6':
		state = PRINT_CHILDREN_WITH_BOTH_PARENTS;
		break;
	case '7':
		state = MUM_DAD;
		break;
	case '8':
		state = GIRLS_BOYS;
		break;
	case '9':
		state = CLEAR;
		break;
	case '0':
		state = EXIT;
		break;
	default:
		state = ERROR;
	}
}

void Print(ostream& out, vector <Human*>& guests, string key) {
	bool empty = true;
	for (auto i : guests) {
		if (i->who() == key) {
			empty = false;
			i->getInfo(out);
		}
	}
	if (empty) {
		if (key == "Parent") {
			out << "Пока нет ни одного родителя\n";
		}
		else {
			out << "Пока нет ни одного ребенка\n";
		}
	}
}

bool InitGuest(istream& in, vector <Human*>& guests) {
	string g, name;
	if (!(in >> g >> name)) return false;
	int id1 = 0;
	in >> id1;
	in >> ws;
	if (!isdigit(in.peek())) {
		guests.push_back(new Parent((g == "MAN" ? Human::MAN : Human::WOMAN), name, id1));
		findParent[id1] = guests.back();
	}
	else {
		int id2;
		in >> id2;
		Human* p1 = findParent[id1];
		Human* p2 = findParent[id2];
		guests.push_back(new Child((g == "MAN" ? Human::MAN : Human::WOMAN), name, p1, p2));
		if (p1 != NULL && p2 != NULL) withBothParents.push_back(guests.back());
		++childrenAmount[id1];
		++childrenAmount[id2];
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	State state = START;
	ofstream out("output.txt");
	out.close();
	vector <Human*> guests;
	ifstream in("guests.txt");
	while (InitGuest(in, guests));
	in.close();
	while (true) {
		switch (state) {
		case EXIT:
			return 0;
		case START: case ERROR:
			state = START;
			StartMenu(state);
			break;
		case F_INIT: {
			ifstream in("guests.txt", ios::ate);
			system("guests.txt");
			while (InitGuest(in, guests));
			in.close();
			state = START;
			break;
		}
					 /*case C_INIT:
						 InitGuest(cin, guests);
						 state = START;
						 break;*/
		case PRINT_PARENTS: {
			ofstream out("output.txt", ios::app);
			Print(out, guests, "Parent");
			Print(cout, guests, "Parent");
			out.close();
			state = START;
			system("pause");
			break;
		}
		case PRINT_CHILDREN: {
			ofstream out("output.txt", ios::app);
			Print(out, guests, "Child");
			Print(cout, guests, "Child");
			out.close();
			state = START;
			system("pause");
			break;
		}
		case PRINT_CHILDREN_WITH_BOTH_PARENTS: {
			ofstream out("output.txt", ios::app);
			if (withBothParents.size() == 0) {
				cout << "Нет ни одного ребенка с двумя родителями.\n";
			}
			for (auto i : withBothParents) {
				i->getInfo(out);
				i->getInfo(cout);
			}
			out.close();
			system("pause");
			state = START;
			break;
		}
		case PRINT_PARENTS_WITH_MAX_CHILDREN: {
			ofstream out("output.txt", ios::app);
			int maximum = -1;
			for (auto i = childrenAmount.begin(); i != childrenAmount.end(); ++i) {
				if (i->second > maximum) {
					maximum = i->second;
				}
			}
			if (maximum == 0 || childrenAmount.size() == 0) {
				cout << "Только родители\n";
			}
			for (auto i = childrenAmount.begin(); i != childrenAmount.end(); ++i) {
				if (i->second == maximum) {
					Human* temp = findParent[i->first];
					if (temp != 0) {
						findParent[i->first]->getInfo(out);
						findParent[i->first]->getInfo(cout);
					}
				}
			}
			state = START;
			system("pause");
			break;
		}
		case MUM_DAD: {
			ofstream out("output.txt", ios::app);
			int dad = 0, mum = 0;
			for (auto i : guests) {
				if (i->who() == "Parent") {
					if (i->getGender() == Human::MAN) {
						++dad;
					}
					else {
						++mum;
					}
				}
			}
			system("cls");
			if (mum > dad) {
				cout << "Мам больше, чем пап.\n";
				out << "Мам больше, чем пап.\n\n";
			}
			else if (mum == dad) {
				cout << "Мам столько же, сколько пап.\n";
				out << "Мам столько же, сколько пап.\n\n";
			}
			else {
				cout << "Пап больше, чем мам.\n";
				out << "Пап больше, чем мам.\n\n";
			}
			out.close();
			state = START;
			system("pause");
			break;
		}
		case CLEAR: {
			ofstream temp("guests.txt");
			temp.close();
			temp.open("output.txt");
			temp.close();
			for (auto i : guests) {
				delete i;
			}
			findParent.clear();
			childrenAmount.clear();
			guests.clear();
			state = START;
			break;
		}
		case GIRLS_BOYS: {
			ofstream out("output.txt", ios::app);
			int boys = 0, girls = 0;
			for (auto i : guests) {
				if (i->who() == "Child")
					if (i->getGender() == Human::MAN) {
						++boys;
					}
					else {
						++girls;
					}
			}
			system("cls");
			if (boys > girls) {
				cout << "Мальчиков больше, чем девочек.\n";
				out << "Мальчиков больше, чем девочек.\n\n";
			}
			else if (boys == girls) {
				cout << "Мальчиков столько же, сколько девочек.\n";
				out << "Мальчиков столько же, сколько девочек.\n\n";
			}
			else {
				cout << "Девочек больше, чем мальчиков.\n";
				out << "Мальчиков столько же, сколько девочек.\n\n";
			}
			out.close();
			state = START;
			system("pause");
			break;
		}
		}
	}
	return 0;
}