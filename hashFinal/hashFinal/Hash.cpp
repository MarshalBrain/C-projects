#include "Hash.h"
 
Hash::Hash() : size(3571), amountOfExist(0) {
	hash.resize(size, nullptr);
}

Hash::Hash(int size = 3571, int AmountOfExist = 0) : size(size), amountOfExist(AmountOfExist) {
	hash.resize(size, nullptr);
}

Hash::~Hash() {
	this->Clean();
}

bool Hash::isEmpty(){
	return this->amountOfExist == 0 ? 1 : 0;
}

bool Hash::isFull() {
	return this->amountOfExist >= size ? 1 : 0;
}

int Hash::Size() {
	return this->amountOfExist;
}

void Hash::Clean() {
	for (int i = 0; i < size; ++i) {
		Node* p = hash[i];
		while (p) {
			Node* pp(p);
			p = p->next;
			delete pp;
		}
		hash[i] = nullptr;
	}
	amountOfExist = 0;
}

std::pair<int, int> Hash::Find(int val) {
	int valHash = getHash(val, *this);
	Node* p = this->hash[valHash];
	int k = 1;
	bool f = 0;
	while (p) {
		if (p->val != val) {
			p = p->next;
			++k;
		}
		else {
			f = 1;
			break;
		}
	}
	return f ? std::make_pair(valHash, k) : std::make_pair(-1, -1);
}

void Hash::Delete(int val) {
	std::pair<int, int> cnt = Find(val);
	if (cnt.first == -1) {
		std::cerr << "It's not exist.\n";
	}
	else {
		Node* p = this->hash[cnt.first];
		if (p->val == val) {
			this->hash[cnt.first] = p->next;
			delete p;
		}
		else {
			for (int k = 1; k < cnt.second - 1; ++k) p = p->next;
			Node* pp = p->next;
			p->next = pp->next;
			delete pp;

		}
//		std::cout << p->val << "\n";
//		std::cout << cnt.first << " " << cnt.second << "\n";
		std::cerr << "Done.\n";
		--amountOfExist;
	}
}

Hash Hash::operator = (Hash const& h) {
	if (this != &h) {
		this->Clean();
		this->Copy(h);
	}
	return *this;
}

int getHash(int val, Hash const& cnt) {
	return val % cnt.size;
}

void Hash::Push(int val) {
	int valHash = getHash(val, *this);
	//std::cout << valHash << "\n";
	if (this->hash[valHash]){
		Node* p = this->hash[valHash];
		while (p) p = p->next;
		Node* pp = new Node(val);
		p->next = pp;
	}
	else {
		this->hash[valHash] = new Node(val);
	}
	++this->amountOfExist;
}


void Hash::Copy(Hash const& h) {
	this->Clean();
	for (int i = 0; i < h.size; ++i) {
		if (h.hash[i]) {
			Node* p = h.hash[i];
			while (p) {

				this->Push(p->val);
				p = p->next;
			}
		}
		else this->hash[i] = nullptr;
	}
}

void Swap(Hash& h1, Hash& h2) {
//	Hash h3(h1.size, h1.amountOfExist);
	std::swap(h1.amountOfExist, h2.amountOfExist);
	std::swap(h1.hash, h2.hash);
	std::swap(h1.size, h2.size);
/*	h3.Copy(h1);
	h1.Copy(h2);
	h2.Copy(h3);*/
}

std::istream& operator >> (std::istream& is, Hash& h) {
	while (is.peek() != '\n') {
		int val;
		is >> val;
		h.Push(val);
	}
	is.ignore(1);
	return is;
}

std::ostream& operator << (std::ostream& os, Hash& h) {
	for (int i = 0; i < h.size; ++i) {
		if (h.hash[i] != nullptr) { 
			Hash::Node* p = h.hash[i];
			while (p != nullptr) {
				os << p->val << " ";
				p = p->next;
			}
		}
	}
	return os;
}

Hash::Node* Hash::operator [] (int val) {
	return this->hash[val];
}