#pragma once
#include <initializer_list> 
#include <iostream>

using namespace std;

class KDynArrTwo;

class KDynArr
{
protected:
	int size;
	int* arr;
public:
	KDynArr() : size(0), arr(nullptr) {};
	KDynArr(int size_)
	{
		size = size_;
		arr = new int[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = 0;
		}
	}
	KDynArr(initializer_list<int> iArr)
	{
		arr = new int[iArr.size()];
		size = iArr.size();
		int i = 0;
		for (auto& x : iArr)
		{
			arr[i++] = x;
		}
	}
	KDynArr(KDynArr const& arr_)
	{
		size = arr_.getSize();
		arr = new int[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = arr_.arr[i];
		}
	}
	KDynArr(KDynArr&& arr_)
	{
		size = arr_.size;
		swap(arr_.arr, arr);
		arr_.clear();
	}

	void clear();
	virtual bool isKDynArrTwo() const;
	virtual KDynArrTwo getKDynArrTwo() const;
	int getSize() const;
	friend void swap(KDynArr& arrL, KDynArr& arrR);

	int operator[](int i) const;
	virtual KDynArr& operator = (KDynArr const& arrR);
	KDynArr& operator = (KDynArrTwo const& arrTwoR);
    virtual KDynArr& operator += (KDynArr const& arrR);
	
	friend ostream& operator << (ostream& os, KDynArr const& arrR);

	virtual ~KDynArr();
};

