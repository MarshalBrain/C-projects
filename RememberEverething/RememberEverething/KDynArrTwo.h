#pragma once
#include "KDynArr.h"
class KDynArrTwo : public KDynArr
{
protected:
	int sizeTwo;
	int* arrTwo;
public:
	KDynArrTwo() : KDynArr()
	{
		/*sizeTwo = 10;
		arrTwo = new int[size];
		for (int i = 0; i < 10; ++i)
		{
			arrTwo[i] = 0;
		}*/
	}
	KDynArrTwo(KDynArr const& arrR) : KDynArr(arrR), arrTwo(nullptr), sizeTwo(0) { };
	KDynArrTwo(initializer_list<int> iArr, initializer_list<int> iArrTwo) : KDynArr(iArr)
	{
		arrTwo = new int[iArrTwo.size()]; // iArrTwo - initializer_list
		sizeTwo = iArrTwo.size();
		int i = 0;
		for (auto& x : iArrTwo)
		{
			arrTwo[i++] = x;
		}
	}
	KDynArrTwo(KDynArrTwo const& arrTwoR)
	{
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
	KDynArrTwo(KDynArrTwo&& arrTwoR)
	{
		size = arrTwoR.size;
		sizeTwo = arrTwoR.sizeTwo;
		swap(arr, arrTwoR.arr);
		swap(arrTwo, arrTwoR.arrTwo);
		arrTwoR.clear();
		arrTwoR.size = 0;
		
		delete[] arrTwoR.arr; // clearing of the first array in object(without it exception by destructer);
		arrTwoR.arr = nullptr;
	}
	KDynArrTwo(size_t size_, size_t sizeTwo_) : KDynArr(size_), sizeTwo(sizeTwo_)
	{
		arrTwo = new int[sizeTwo];
		for (int i = 0; i < sizeTwo; ++i)
		{
			arrTwo[i] = 0;
		}
	}



	void clear();
	int getSize() const;
	int getSizeTwo() const;
	bool isKDynArrTwo() const;
	KDynArrTwo getKDynArrTwo() const;
	const int* getArr() const;
	const int* getArrTwo() const;
	friend void swap(KDynArrTwo& arrTwo1, KDynArrTwo& arrTwo2);


	friend ostream& operator << (ostream& os, KDynArrTwo const& arrTwoR);
	KDynArrTwo& operator += (KDynArr const& arrR) override;
	KDynArrTwo& operator += (KDynArrTwo const& arrTwoR);
	KDynArrTwo& operator = (KDynArrTwo const& arrTwoR);
	KDynArrTwo& operator = (KDynArr const& arrR) override;


	~KDynArrTwo();
};

