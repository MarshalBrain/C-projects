#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>

//Standart Hash func.
template <typename T> int getHashStandart(T value, int _Key) {
	return (int)(value.num + value.denom) % _Key;
}

//myStruct
template <typename T>
struct Node {
	Node() : val(), next() {}
	Node(T val, Node<T>* next = nullptr) : val(val), next(next) {}
	Node(Node<T>& _arg) : val(_arg.val), next(_arg.next) {}

	T val;
	Node<T>* next;
};

template <typename T>
struct NodeEm {
	template<typename ... Args>
	NodeEm(Args ... _args) : val(_args...), next(nullptr) {}

	T val;
	Node<T>* next;
};

template <typename T>
class Iterator;

template <typename T>
class Hash {
private:
	int amountOfExist;
	int _begin;
	int _end;
public:
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	friend class Iterator<T>;

	int size;
	std::vector<Node<T>*> hash;
	int(*getHash_)(T, int);

	//Основные методы класса Hash
	Hash() : hash(3572), amountOfExist(0), size(3571) {
		getHash_ = getHashStandart;
		_begin = size;
		_end = 0;
	}

	Hash(int size) : hash(size + 1), amountOfExist(0), size(size) {
		getHash_ = getHashStandart;
		_begin = size;
		_end = 0;
	}

	Hash(int size, int(*GetHash_)(T, int) = getHashStandart) : size(size), hash(size + 1), amountOfExist(0) {
		getHash_ = GetHash_;
		_begin = size;
		_end = 0;
	}

	Hash(Hash<T> const& _arg) {
		this->Copy(_arg);
	}

	Hash(Hash<T>&& _arg) {
		this->Copy(_arg);
		_arg.Clean();
	}

	Hash(std::initializer_list<T> _arg) {
		hash.resize(_arg.size() + 1);
		size = (int)_arg.size();
		_begin = size;
		_end = 0;
		getHash_ = getHashStandart;
		for (auto it = _arg.begin(); it != _arg.end(); ++it) {
			Push(*it);
		}
	}

	~Hash() {
		this->Clean();
	}

	bool isEmpty() {
		return this->amountOfExist == 0 ? 1 : 0;
	}

	bool isFull() {
		return this->amountOfExist >= size ? 1 : 0;
	}

	int Size() {
		return this->amountOfExist;
	}

	void Clean() {
		for (int i = 0; i < size; ++i) {
			Node<T>* p = hash[i];
			while (p) {
				Node<T>* pp(p);
				p = p->next;
				delete pp;
			}
			hash[i] = nullptr;
		}
		amountOfExist = 0;
		size = 0;

	}

	void Find(T val) {
		int keyHash = getHash_(val, &(*this));
		Node<T>* p = this->hash[keyHash];
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
		return f ? std::make_pair(keyHash, k) : std::make_pair(-1, -1);
	}

	void Delete(T val) {
		std::pair<int, int> cnt = Find(val);
		try {
			if (cnt.first == -1) {
				throw "It's not exist.\n";
			}
			Node<T>* p = this->hash[cnt.first];
			if (p->val == val) {
				this->hash[cnt.first] = p->next;
				delete p;
			}
			else {
				for (int k = 1; k < cnt.second - 1; ++k) p = p->next;
				Node<T>* pp = p->next;
				p->next = pp->next;
				delete pp;
			}
			std::cerr << "Done.\n";
			--amountOfExist;
		}
		catch (const char* report) {
			cerr << report;
		}
	}

	void Push(T val) {
		int keyHash = getHash_(val, size);

		_begin = std::min(keyHash, _begin);
		_end = std::max(keyHash, _end);

		if (this->hash[keyHash]) {
			Node<T>* p = this->hash[keyHash];
			while (p->next != nullptr) p = p->next;
			Node<T>* pp = new Node<T>(val);
			p->next = pp;
		}
		else {
			hash[keyHash] = new Node<T>(val);
		}
		++amountOfExist;
	}

	template <typename ... Args>
	void Emplace(Args const& ... _args) {

		Node<T> *p = (Node<T> *) new NodeEm<T>(_args...);
		int Key = getHash_(p->val, size);
		_begin = std::min(Key, _begin);
		_end = std::max(Key, _end);

		Node<T> *it = hash[Key];

		if (it) {
			while (it->next != nullptr) {
				it = it->next;
			}
			it->next = p;
		}
		else {
			hash[Key] = p;
		}
		++amountOfExist;
	}

	void Copy(Hash<T> const& h) {
		Clean();
		hash.resize(h.size + 1);
		size = h.size;
		getHash_ = h.getHash_;
		_begin = h._begin;
		_end = h._end;
		amountOfExist = h.amountOfExist;
		for (int i = 0; i < h.size; ++i) {
			if (h.hash[i]) {
				Node<T>* p = h.hash[i];
				while (p) {
					Push(p->val);
					p = p->next;
				}
			}
			else hash[i] = nullptr;
		}
	}

	void Move(Hash<T>& _arg) {
		hash = _arg.hash;
		size = _arg.size;
		hash.resize(size + 1);
		amountOfExist = _arg.amountOfExist;
		getHash_ = _arg.getHash_;
		_begin = _arg._begin;
		_end = _arg._end;
		for (int i = 0; i < _arg.size; ++i) {
			_arg.hash[i] = nullptr;
		}
		_arg.size = 0;
		_arg.amountOfExist = 0;
		_arg.getHash_ = getHashStandart;
		_arg.hash.resize(0);
		_arg._begin = _arg._end = 0;
	}

	void Swap(Hash<T>& h1, Hash<T>& h2) {
		std::swap(h1.amountOfExist, h2.amountOfExist);
		h1.hash.swap(h2.hash);
		std::swap(h1.size, h2.size);
	}

	//Перегруженные операторы класса Hash
	friend std::istream& operator >> (std::istream& is, Hash<T>& h) {
		while (is.peek() != '\n') {
			T val;
			is >> val;
			h.Push(val);
		}
		is.ignore(1);
		return is;
	}

	friend std::ostream& operator << (std::ostream& os, Hash<T>& h) {
		for (int i = 0; i < h.size; ++i) {
			if (h.hash[i] != nullptr) {
				Hash::Node<T>* p = h.hash[i];
				while (p != nullptr) {
					os << p->val << " ";
					p = p->next;
				}
			}
		}
		return os;
	}

	Node<T>* operator [] (int val) {
		return this->hash[val];
	}

	Hash<T>& operator = (Hash<T> const& _arg) {
		if (this != &_arg) {
			Copy(_arg);
		}
		return *this;
	}

	Hash<T>& operator = (Hash<T>&& _arg) {
		if (this != &_arg) {
			Move(_arg);
		}
		return *this;
	}

	friend class Iterator<T>;

	iterator begin() {
		if (_begin <= _end)	return iterator(hash[_begin], this, _begin);
		else return iterator();
	}

	const_iterator begin() const {
		if (_begin <= _end)	return const_iterator(hash[_begin],(const Hash<const T> *) this, _begin);
		else return const_iterator();
}

	iterator end() {
		if (_begin <= _end) return iterator(hash[_end + 1], this, _end + 1);
		else return iterator();
	}
	
	const_iterator end() const {
		if (_begin <= _end) return const_iterator((Node<const T>*)hash[_end + 1], (const Hash<const T>*)this, _end + 1);
		else return const_iterator();
	}

	const_iterator cbegin() {
		if (_begin <= _end)	return const_iterator((Node<const T>*)hash[_begin], (const Hash<const T> *) this, _begin);
		else return const_iterator();
	}
	
	const_iterator cbegin() const{
		if (_begin <= _end)	return const_iterator((Node<const T>*)hash[_begin], (const Hash<const T> *) this, _begin);
		else return const_iterator();
	}

	const_iterator cend() {
		if (_begin <= _end) return const_iterator((Node<const T>*)hash[_end + 1], (const Hash<const T> *) this, _end + 1);
		else return const_iterator();
	}

	const_iterator cend() const {
		if (_begin <= _end) return const_iterator((Node<const T>*)hash[_end + 1], (Hash<const T> const *) this, _end + 1);
		else return const_iterator();
	}
};

template <typename T>
class Iterator
{
public:
	typedef T value_type;
	typedef T* Pointer;
	typedef T& reference;
	typedef std::forward_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	Iterator() : pointer(), pointerOnHash(), counter() {}
	Iterator(Node<T>* _pointer, Hash<T>* _pointerOnHash, int Counter = 0) : pointer(_pointer), pointerOnHash(_pointerOnHash), counter(Counter) {}
	Iterator(Node<const T>* _pointer, Hash<const T> const* _pointerOnHash, int Counter = 0) : pointer(_pointer), pointerOnHash(_pointerOnHash), counter(Counter) {}
	Iterator(const Iterator &other) {
		if (this != &other) {
			pointer = other.pointer;
			pointerOnHash = other.pointerOnHash;
			counter = other.counter;
		}
	}

	bool operator!=(Iterator const& other) const {
		bool f = 1;
		if (pointer == other.pointer) f = 0;
		return f;
	}

	bool operator==(Iterator const& other) const {
		bool f = 1;
		if (pointer != other.pointer) f = 0;
		return f;
	}

	Iterator& operator++() {
		this->helper_for_postpref_inc();
		return *this;
	}

	Iterator operator++(int i) {
		Iterator<T> temp(pointer, *this);
		this->helper_for_postpref_inc();
		return temp;
	}

	Node<T>& operator *() {
		return *pointer;
	}

	Node<T>* operator->() {
		return pointer;
	}
private:
	Iterator & helper_for_postpref_inc() {
		while (pointer == nullptr && counter < pointerOnHash->size) {
			pointer = pointerOnHash->hash[counter];
			++counter;
		}
		pointer = pointer->next;
		if (pointer == nullptr) {
			while (pointer == nullptr && counter < pointerOnHash->size) {
				++counter;
				pointer = pointerOnHash->hash[counter];
			}
			if (counter == pointerOnHash->size) *this = pointerOnHash->end();
		}
		return *this;
	}

	Node<T> *pointer;
	Hash<T> const *pointerOnHash;
	int counter;
};
