#pragma once
#include <vector>
#include <iostream>
#include <utility>

class Hash {
private:
	int amountOfExist;
	struct Node {
		Node(int val, Node* next = nullptr) : val(val), next(next) {}

		int val;
		Node* next;

	/*	Node* operator ++() {
			return this->next;
		}
*/	};
public:
	int size;
	std::vector<Node*> hash;

	Hash();
	Hash operator = (Hash const&);
	Hash(int, int);

	~Hash();
	
	bool isEmpty();

	bool isFull();

	friend int getHash(int, Hash const&);

	int Size();

	void Clean();

	std::pair<int, int> Find(int);

	void Delete(int);

	void Push(int);

	void Copy(Hash const &);

	friend void Swap(Hash&, Hash&);

	friend std::ostream& operator << (std::ostream&, Hash&);

	friend std::istream& operator >> (std::istream&, Hash&);

	Node* operator [] (int);

};