#include "DynArr.h"
#include "DynArrTwo.h"

DynArr::DynArr() : sizeA(0) {
	a = nullptr;
}

DynArr::DynArr(std::initializer_list<int> _arg) {
	a = new int[_arg.size()];
	sizeA = _arg.size();
	int j = 0;
	for (auto it : _arg) {
		a[j] = it;
		++j;
	}
}

DynArr::DynArr(DynArr const& _arg) {
	Copy(_arg);
}

DynArr::DynArr(DynArr&& _arg) {
	Move(_arg);
}

DynArr::~DynArr() {
	clear();
}

DynArr& DynArr::operator = (DynArr const& _arg) {
	if (this != &_arg) {
		if (_arg.isDynArrTwo() && isDynArrTwo()) {
			this->getDynArrTwo() = _arg.getDynArrTwo();
		}
		else {
			Copy(_arg);
		}
	}
	return *this;
}
/*
DynArr& DynArr::operator = (DynArrTwo const& _arg) {
	if (this != &_arg) {
		if (this->isDynArrTwo()) {
			*this = this->getDynArrTwo();
		}
		sizeA = _arg.sizeA;
		delete[] a;
		a = new int[sizeA];

		for (int i = 0; i < sizeA; ++i) {
			a[i] = _arg.a[i];
		}
	}
	return *this;
}
*/
DynArr& DynArr::operator = (DynArr&& _arg) {
	if (this != &_arg) Move(_arg);
	return *this;
}

DynArr& DynArr::operator += (DynArr const& _arg) {
	for (int i = 0; i < std::min(sizeA, _arg.sizeA); ++i) {
		a[i] += _arg.a[i];
	}
	return *this;
}

bool DynArr::operator == (DynArr const& _arg) const {
	if (a == _arg.a) return 1;
	else return 0;
}

bool DynArr::operator != (DynArr const& _arg) const {
	return !(*this == _arg);
}

int DynArr::operator [] (int i) const {
	return a[i];
}

DynArrTwo DynArr::getDynArrTwo() const {
	return DynArrTwo(*this);
}

int DynArr::size() const {
	return sizeA;
}

bool DynArr::isDynArrTwo() const {
	return false;
}

void DynArr::Copy(DynArr const& _arg) {
	delete[] a;

	sizeA = _arg.sizeA;
	a = new int[sizeA];
	for (int i = 0; i < sizeA; ++i) {
		a[i] = _arg.a[i];
	}
}

void DynArr::Move(DynArr& _arg) {
	std::swap(a, _arg.a);

	sizeA = _arg.sizeA;

	_arg.clear();
}

void DynArr::CopyArrays(int *_arg, int size) {
	delete[] a;
	a = new int[size];

	for (int i = 0; i < size; ++i) {
		a[i] = _arg[i];
	}
}

int* DynArr::getPointerTwo() const{
	return nullptr;
}

int DynArr::getSizeTwo() const {
	return 0;
}
void DynArr::print(std::string _arg) const{
	std::cout << _arg;
	for (int i = 0; i < sizeA; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << "\n";
}

void DynArr::clear() {
	sizeA = 0;
	delete[] a;
	a = nullptr;
}