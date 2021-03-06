// Remember_All.cpp: определяет точку входа для консольного приложения.
//
#include "DynArrTwo.h"


int main()
{
	DynArr a1 = { 2, 4, 3, 23, 17 };
	DynArr a2(a1);
	DynArr a3;

	a2.print("a2: ");

	a2 += a1;

	a2.print("a2: ");

	a3 = std::move(a1);
	
	a1.print("a1: ");


	DynArrTwo b1({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo b2, b3, b4(b1), b5(b1);

	a2 += b1;


	b1 += a3;

	b1.print("b1: ");

	DynArr *pb1 = new DynArrTwo({ 21, 23, 54 }, { 29, 31, 46 });
	DynArr *pb2 = new DynArrTwo({ 21, 23, 54 }, { 29, 31, 46 });
	DynArr *pb3 = new DynArrTwo({ 21, 23, 54, 99 }, { 29, 31 });

	DynArrTwo *d21 = new DynArrTwo({ 1, 2, 54 }, { 2, 1, 4 });
	DynArrTwo *d22 = new DynArrTwo({ 2, 3, 4 }, { 29, 31, 46 });


	*d21 = *d22;

	d21->print("d21");

	*pb3 = *pb2;

	pb3->print("pb3");
	a2 += *pb1;

/*	pb3->print("pb3: ");
	

	pb3->print("pb3: ");*/

	delete d21;
	delete d22;
	delete pb1;
	delete pb2;
	delete pb3;
    return 0;
}

