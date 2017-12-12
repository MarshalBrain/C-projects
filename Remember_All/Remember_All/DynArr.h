#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

class DynArrTwo;

class DynArr {
public:
	DynArr();

	DynArr(std::initializer_list<int>);

	DynArr(DynArr const&);

	DynArr(DynArr&&);

	virtual ~DynArr();

	virtual DynArr& operator = (DynArr const&);

//	DynArr& operator = (DynArrTwo const&);

	DynArr& operator = (DynArr&&);

	virtual DynArr& operator += (DynArr const&);

	bool operator == (DynArr const&) const;

	bool operator != (DynArr const& _arg) const;

	int operator [] (int i) const;

	virtual DynArrTwo getDynArrTwo() const;

	virtual int size() const;

	virtual bool isDynArrTwo() const;

	virtual void Copy(DynArr const& _arg);

	void CopyArrays(int *_arg, int size);

	virtual void Move(DynArr& _arg);

	virtual void print(std::string) const;

	virtual void clear();

	virtual int* getPointerTwo() const;

	virtual int getSizeTwo() const;

	int sizeA;
	int* a;

};