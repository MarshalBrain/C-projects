// RememberEverething.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KDynArr.h"
#include "KDynArrTwo.h"

KDynArr f()
{
	KDynArr d({ 1, 2, 3 });
	return d;
}

int main()
{
	/*cout << "Move constructor:\n";
	KDynArr arr({ 1, 3, 5, 7 });
	cout << "moving object: " << arr << endl;
	KDynArr arr1(move(arr));
	cout << arr << " -> " << arr1 << endl;*/
	//______________________________________
/*
	KDynArr arr1;
	arr1 = f();
	cout <<  arr1 << endl;
*/
	/*arr = arr;
	arr = arr1;*/
	//______________________________________
	/*cout << "\n+=" << endl;
	KDynArr arr2({ 2, 4, 6, 3, 10 });
	cout << arr << " += " << arr2 << " -> ";
	arr += arr2; 
	cout << arr << endl;*/
	
	//___________________________________________
	/*cout << "\nMove constructor KDynArrayTwo:\n";
	KDynArrTwo arrTwo({ 3, 3, 3, 5 }, { 2, 4, 10, 14 });
	cout << "Moving object: " << arrTwo << endl;
	KDynArrTwo arrTwo1(move(arrTwo));
	cout << arrTwo << " -> " << arrTwo1 << endl; */
	//________________________________________

	/*KDynArr *pb1 = new KDynArrTwo({ 1, 2, 3, 4 }, { 5, 6, 7, 8 });
	KDynArr *pb2 = new KDynArrTwo({ 5, 5, 5, 5 }, { 1, 1, 1, 1 });
	cout << "\n" << *pb2 << " += " << *pb1 << " -> ";
	*pb2 += *pb1;
	cout << *pb2 << endl;
	*/
	//cout << "\n";

	KDynArrTwo b3;
	KDynArr *pb3 = new KDynArrTwo({ 21, 33, 54 }, { 29, 31, 46 });

	b3 = (*pb3);
	KDynArr *pb4 = new KDynArrTwo({ 1, 1, 1, 1, 1, 1 }, { 1, 2 });
	cout << *pb4 << endl << *pb3 << endl;
	*pb4 = *pb3;
	cout << "= " << *pb4 << endl;

	KDynArrTwo d1({ 1, 1, 2, 2 }, { 103, 104, 105 });
	KDynArrTwo d2({ 99, 999, 9999 }, { 1009999, 100999, 10999 });
	cout << d1 << endl << d2 << endl;
	d1 = d2;
	cout << d1 << endl;



    return 0;
}

