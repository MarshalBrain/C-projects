#include "stdafx.h"
#include "KDynArr.h"
#include <assert.h>
#include <string>
#include "KDynArrTwo.h"
#include <algorithm>


void KDynArr::clear()
{
	delete[] arr;
	size = 0;
}
bool KDynArr::isKDynArrTwo() const
{
	return false;
}
KDynArrTwo KDynArr::getKDynArrTwo() const
{
	return KDynArrTwo(*this);
}
int KDynArr::getSize() const 
{
	return size;
}

void swap(KDynArr& arrL, KDynArr& arrR)
{
	swap(arrL.size, arrR.size);
	swap(arrL.arr, arrR.arr);
}

int KDynArr::operator[](int i) const
{
	try {
		if (i < 0 || i >= size)
		{
			//cerr << "\nWrond index: " << i << endl;
			//return NULL;
			throw "Wrong index.";
		}
	}
	catch (const char* s)
	{
		cout << s << endl;
		throw;
	}
	return arr[i];
}

KDynArr& KDynArr::operator = (KDynArr const& arrR)
{
	if (this != &arrR)
	{

		clear();
		size = arrR.size;
		arr = new int[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = arrR[i];
		}
	}
	return *this;
}
KDynArr& KDynArr::operator = (KDynArrTwo const& arrTwoR)
{
	clear();
	size = arrTwoR.getSize();
	arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = arrTwoR.getArr()[i];
	}
	
	return *this;
}

KDynArr& KDynArr::operator += (KDynArr const& arrR)
{
	if (arrR.isKDynArrTwo()) { *this += arrR.getKDynArrTwo(); }
	else
	{

		for (int i = 0; i < min(arrR.size, size); ++i)
		{
			arr[i] += arrR[i];
		}
	}
		return *this;
}


ostream& operator << (ostream& os, KDynArr const& arrR)
{
	if (arrR.isKDynArrTwo()) { cout << arrR.getKDynArrTwo();}
	else
	{
		os << "{ ";
		for (int i = 0; i < arrR.getSize(); ++i)
		{
			os << arrR[i] << " ";
		}
		if (arrR.getSize() == 0)
		{
			os << "Empty array.";
		}
		os << "}";
	}
	return os;
}

 KDynArr::~KDynArr()
 {
	 clear();
 }
