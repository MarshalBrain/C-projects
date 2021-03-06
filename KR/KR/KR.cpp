// KR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class List {
public:
	List() : begin(nullptr), end(nullptr) {}
	void pushBack(int x);
	void printList();
	void removeChetn();
	void findTripleMax();
	void invertion(int);

private:
	struct Node {
		int data;
		Node * next;
		Node * pred;
	};
	Node *begin;
	Node *end;
};

int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	std::cin >> n;
	List myList;
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		myList.pushBack(x);
	}
	std::cout << "Изначальный список:\n";
	myList.printList();

	myList.removeChetn();
	myList.printList();

	myList.findTripleMax();
	myList.printList();

	myList.invertion(n);
	myList.printList();

	return 0;
}

void List::pushBack(int x) {
	Node *temp = new Node;
	temp->data = x;
	if (begin == 0) {
		temp->next = temp->pred = nullptr;
		begin = end = temp;
	}
	else {
		temp->next = 0;
		temp->pred = end;
		end->next = temp;
		end = temp;
	}
}

void List::printList() {
	Node *p = begin;
	while (p != nullptr) {
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout << "\n";
}

void List::removeChetn() {
	if (begin == end) {
		std::cout << "Список после перемещения элементов с чётными номерами в конец:\n";
		return;
	}
	int k = 0;
	Node *p = begin;
	static Node *new_last = end;
	static Node *new_first = begin->next;
	while (true) {
		if (!(k & 1)) {
			Node *cnt = p;
			p = p->next;
			new_last->next = cnt;
			if (cnt->pred != nullptr) {
				cnt->pred->next = cnt->next;
				if (cnt->next != nullptr) cnt->next->pred = cnt->pred;
			}
			cnt->next->pred = nullptr;
			cnt->pred = new_last;
			cnt->next = nullptr;
			new_last = new_last->next;
		}
		if (k & 1) p = p->next;
		if (p == begin) break;
		++k;
	}
	begin = new_first;
	end = new_last;
	std::cout << "Список после перемещения элементов с чётными номерами в конец:\n";
}

void List::findTripleMax() {
	int k = 1;
	if (begin == nullptr) {
		std::cout << "Извините, но список пустой, невозможно найти максимальный элемент, номер которого кратен 3-м.\n";
		return;
	}
	int ans = begin->data, num = 0;
	Node *p = begin->next;
	while (p) {
		if (k % 3 == 0 && p->data > ans) {
			ans = p->data;
			num = k;
		}
		++k;
		p = p->next;
	}
	std::cout << "Максимальный элемент, номер которого кратен 3-м: " << ans << " \nЕго номер: " << num << "\n";
}

void List::invertion(int n) {
	if (begin == nullptr) {
		std::cout << "Извините, но список пустой, невозможно инвертировать элементы, номера которых кратны 3-м.\n";
		return;
	}
	int left = 0, right = n - 1;
	Node *pLeft = begin;
	Node *pRight = end;
	while (right % 3 != 0) {
		right--;
		pRight = pRight->pred;
	}

	while (left < right) {
		if (left % 3 == 0) std::swap(pLeft->data, pRight->data);
		++left, --right;
		pLeft = pLeft->next;
		pRight = pRight->pred;
	}
	std::cout << "Список с инвертированной подпоследовательностью элементов, номера которых крытны 3-м:\n";
}