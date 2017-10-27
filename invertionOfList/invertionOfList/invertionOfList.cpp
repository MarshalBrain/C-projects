// invertionOfList.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

struct Node {
public:
	Node(int aData = 0, Node * aNext = nullptr) : data(aData), next(aNext) {};
	int data;
	Node *next;
};


class ZList {
public:
	ZList();
	ZList(Node*, Node*);
	ZList(const ZList&);
	~ZList();
	//конструкторы копирования и обычный, деструктор, операторы присваивания и вывода 

	ZList& inverse();

	void pushBack(int);

	void pushFront(int);

	void printList();

	void clear();

	ZList& copyList(ZList&);

	friend ostream& operator <<(ostream &os, ZList const &val) {
		Node *p = val.begin;
		while (p) {
			os << p->data << " ";
			p = p->next;
		}
		return os;
	}

	ZList& operator = (ZList const&); 

	Node *begin = nullptr;
	Node *end = nullptr;
};

int main()
{
	int n;
	cin >> n;
	ZList myList;
	for (int i = 0; i < n; ++i) {
		int val;
		cin >> val;
		myList.pushBack(val);
	}
	cout << myList << "\n";
	ZList newList(myList);
	cout << myList << "\n" << newList << "\n";
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int val;
		cin >> val;
		newList.pushBack(val);
	}
	cout << newList << "\n";
	return 0;
}

ZList::ZList() : begin(nullptr), end(nullptr) {}

ZList::ZList(Node *Begin, Node *End) : begin(Begin), end(End) {}

ZList::ZList(const ZList& val)
{
	begin = end = nullptr;
	Node *p = val.begin;
	while (p)
	{
		pushBack(p->data);
		p = p->next;
	}
};

ZList::~ZList() {
	this->clear();
}

ZList& ZList::operator = (ZList const& val) {
	if (this != &val) {
		Node *p = val.begin;
		this->clear();
		while (p) {
			this->pushBack(p->data);
			p = p->next;
		}
	}
	return *this;
}

ZList& ZList::inverse() {
	Node *P1 = nullptr;
	Node *P2 = this->begin;
	Node *cnt;
	while (P2 != nullptr) {
		cnt = P2->next;
		P2->next = P1;
		P1 = P2;
		P2 = cnt;
	}
	swap(this->begin, this->end);
	return *this;
}

ZList& ZList::copyList(ZList &val) {
	Node *p1 = val.begin;
	this->clear();
	while (p1) {
		this->pushBack(p1->data);
		p1 = p1->next;
	}
	return *this;
}

void ZList::clear() {
	Node *p = this->begin;
	while (p) {
		Node *pp = p;
		p = p->next;
		delete pp;
		//cout << p->data << "?" << endl;
	}
}

void ZList::pushFront(int val) {
	Node *temp = new Node(val, begin);
	if (begin == nullptr) {
		begin = new Node;
		begin = end = temp;
	}
	else {
		begin = temp;
	}
}

void ZList::pushBack(int val) {
	Node *temp = new Node(val);
	if (begin == nullptr) {
		begin = end = temp;
	}
	else {
		end->next = temp;
		end = temp;
	}
}

void ZList::printList() {
	Node *p = begin;
	while (p) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << "\n";
} 