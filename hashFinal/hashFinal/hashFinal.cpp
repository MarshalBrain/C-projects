// hashTable2.cpp : Defines the entry point for the console application.
//
#include "Hash.h"
#include <vector>
#include <iostream>

int main()
{
	Hash b;
	std::cin >> b;


	//	for (int i = 0; i < 10; ++i) b.Push(i);

	//	std::cout << b << "\n";

	Hash c;

	std::cin >> c;
	c.Clean();
//	c = b;
	/*	c.Delete(1);
	//	std::cout << ans.first << " " << ans.second;
	std::cout << c.Size() << "\n";
	c.Clean();
	std::cout << c.isEmpty() << "\n";
	std::cin >> c;
	std::cout << c.isFull() << "\n";
	std::cout << c[0] << "\n";*/
	std::cout << b << "\n" << c;
	return 0;
}

