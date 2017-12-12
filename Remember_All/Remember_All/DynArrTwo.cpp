#include "DynArrTwo.h"

DynArrTwo::DynArrTwo() : DynArr(), sizeB(0) {
	b = nullptr;
}

DynArrTwo::DynArrTwo(std::initializer_list<int> _arg1, std::initializer_list<int> _arg2) : DynArr(_arg1) {
	b = new int[_arg2.size()];
	sizeB = _arg2.size();
	int j = 0;
	for (auto it : _arg2) {
		b[j] = it;
		++j;
	}
}

DynArrTwo::DynArrTwo(DynArrTwo const& _arg) {
	Copy(_arg);
}

DynArrTwo::DynArrTwo(DynArr const& _arg) {
	sizeA = _arg.size();
	a = new int[sizeA];
	sizeB = 0;
	b = nullptr;

	for (int i = 0; i < sizeA; ++i) {
		a[i] = _arg.a[i];
	}
}

DynArrTwo::DynArrTwo(DynArrTwo&& _arg) {
	Move(_arg);
}

DynArrTwo::~DynArrTwo() {
	clear();
}

DynArrTwo& DynArrTwo::operator = (DynArrTwo const& _arg) {
	if (*this != _arg) Copy(_arg);
	return *this;
}

DynArrTwo& DynArrTwo::operator = (DynArr const& _arg) {
	if (_arg.isDynArrTwo()) {
		*this = _arg.getDynArrTwo();
	}
	else {
		sizeA = _arg.size();
		CopyArrays(_arg.a, sizeA);
		sizeB = 0;
		b = nullptr;
	}
	return *this;
}

/*DynArrTwo& DynArrTwo::operator += (DynArrTwo const& _arg) {
	for (int i = 0; i < std::min(sizeA, _arg.sizeA); ++i) {
		a[i] += _arg.a[i];
	}

	for (int i = 0; i < std::min(sizeB, _arg.sizeB); ++i) {
		b[i] += _arg.b[i];
	}
	return *this;
}*/

int* DynArrTwo::getPointerTwo() const {
	return b;
}

int DynArrTwo::getSizeTwo() const {
	return sizeB;
}

DynArrTwo& DynArrTwo::operator += (DynArr const& _arg) {
	if (_arg.isDynArrTwo()) {
		int* ptr = getPointerTwo();

		for (int i = 0; i < std::min(sizeB, _arg.getSizeTwo()); ++i) {
			b[i] += ptr[i];
		}
	}
	for (int i = 0; i < std::min(sizeA, _arg.sizeA); ++i) {
		a[i] += _arg[i];
	}
	return *this;
}

bool DynArrTwo::isDynArrTwo() const {
	return 1;
}

DynArrTwo& DynArrTwo::operator = (DynArrTwo&& _arg) {
	if (*this != _arg) Move(_arg);
	return *this;
}

bool DynArrTwo::operator == (DynArrTwo const& _arg) const {
	if (a == _arg.a) return 1;
	else return 0;
}

bool DynArrTwo::operator != (DynArrTwo const& _arg) const {
	return !(*this == _arg);
}

void DynArrTwo::Copy(DynArrTwo const& _arg) {
	if (b && a) clear();
	if (a) DynArr::clear();

	sizeA = _arg.sizeA;
	a = new int[sizeA];
	for (int i = 0; i < sizeA; ++i) {
		a[i] = _arg.a[i];
	}

	sizeB = _arg.sizeB;
	b = new int[sizeB];
	for (int i = 0; i < sizeB; ++i) {
		b[i] = _arg.b[i];
	}
}

void DynArrTwo::Move(DynArrTwo& _arg) {
	std::swap(a, _arg.a);
	sizeA = _arg.sizeA;

	std::swap(b, _arg.b);
	sizeB = _arg.sizeB;

	delete[] _arg.a;
	delete[] _arg.b;

	_arg.a = _arg.b = nullptr;
	_arg.sizeA = _arg.sizeB = 0;
}

DynArrTwo DynArrTwo::getDynArrTwo() const {
	return (*this);
}

void DynArrTwo::print(std::string _arg) const {
	std::cout << _arg;
	for (int i = 0; i < sizeA; ++i) {
		std::cout << a[i] << " ";
	}

	std::cout << " & ";

	for (int i = 0; i < sizeB; ++i) {
		std::cout << b[i] << " ";
	}

	std::cout << "\n";
}

void DynArrTwo::clear() {
	sizeB = 0;

	delete[] b;

	b = nullptr;
}
