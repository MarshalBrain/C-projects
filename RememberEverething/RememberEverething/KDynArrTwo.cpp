#include "stdafx.h"
#include "KDynArrTwo.h"
#include <algorithm>


ostream& operator << (ostream& os, KDynArrTwo const& arrTwoR)
{
	os << "{ { ";
	if (arrTwoR.size == 0)
		os << "Empty array ";
	else
	{
		for (int i = 0; i < arrTwoR.size; ++i)
		{
			os << arrTwoR.arr[i] << " ";
		}
	}

	os << "}, { ";
	
	if (arrTwoR.sizeTwo == 0)
		os << "Empty array ";
	else
	{
		for (int i = 0; i < arrTwoR.sizeTwo; ++i)
		{
			os << arrTwoR.arrTwo[i] << " ";
		}
	
	}
	os << "} }";
	return os;
}

KDynArrTwo& KDynArrTwo::operator = (KDynArrTwo const& arrTwoR)
{
	if (this != &arrTwoR)
	{

		clear();
		KDynArr::clear();

		size = arrTwoR.size;
		sizeTwo = arrTwoR.sizeTwo;

		arr = new int[size];
		arrTwo = new int[sizeTwo];

		for (int i = 0; i < size; ++i)
		{
			arr[i] = arrTwoR.arr[i];
		}
		for (int i = 0; i < sizeTwo; ++i)
		{
			arrTwo[i] = arrTwoR.arrTwo[i];
		}
	}
	return *this;
}
KDynArrTwo& KDynArrTwo::operator = (KDynArr const& arrR)
{
	if (arrR.isKDynArrTwo())
	{
		*this = arrR.getKDynArrTwo();
	}
	else
	{
		KDynArr::clear();
		size = arrR.getSize();
		arr = new int[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = arrR[i];
		}
	}
	return *this;
}

KDynArrTwo& KDynArrTwo::operator += (KDynArr const& arrR)
{
	if (arrR.isKDynArrTwo()) { *this += arrR.getKDynArrTwo(); }
	else
	{
		for (int i = 0; i < min(size, arrR.getSize()); ++i)
		{
			arr[i] += arrR[i];
		}
	}
	return *this;
}
KDynArrTwo& KDynArrTwo::operator += (KDynArrTwo const& arrTwoR)
{
	
		for (int i = 0; i < min(size, arrTwoR.size); ++i)
		{
			arr[i] += arrTwoR.getArr()[i];
		}
		for (int i = 0; i < min(sizeTwo, arrTwoR.sizeTwo); ++i)
		{
			arrTwo[i] += arrTwoR.getArrTwo()[i];
		}
	return *this;
}


void KDynArrTwo::clear()
{
	sizeTwo = 0;
	delete[] arrTwo;
}
bool KDynArrTwo::isKDynArrTwo() const
{
	return true;
}
KDynArrTwo KDynArrTwo::getKDynArrTwo() const
{
	return (*this);
}
int KDynArrTwo::getSize()  const
{
	return size;
}
int KDynArrTwo::getSizeTwo() const
{
	return sizeTwo;
}
const int* KDynArrTwo::getArr() const
{
	return arr;
}
const int* KDynArrTwo::getArrTwo() const
{
	return arrTwo;
}

void swap(KDynArrTwo& arrTwo1, KDynArrTwo& arrTwo2)
{
	swap(arrTwo1.size, arrTwo2.size);
	swap(arrTwo1.arr, arrTwo2.arr);
	swap(arrTwo1.sizeTwo, arrTwo2.sizeTwo);
	swap(arrTwo1.arrTwo, arrTwo2.arrTwo);
}


KDynArrTwo::~KDynArrTwo()
{ 
	clear();
}
