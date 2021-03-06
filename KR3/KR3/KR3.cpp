// KR3.cpp: определяет точку входа для консольного приложения.
//
#include "polygon.h"
#include <vector>
#include <string>
#include <iostream>

void getAns(std::vector<Point*> &mass) {
	for (int i = 1; i < mass.size(); ++i) {
		if (*mass[i - 1] < *mass[i]) {
			std::cout << i - 1 << " " << i;
			return;
		}
	}
}

int main()
{
	Point t1(1, 1), to, t2(2, 1);
	P p1(2, 2, 3, 4), p2(1, 2, 3, 4), p3;

/*	std::cout << t1 << "\n";
	std::cout << p1 << "\n----------------------------\n";*/
	
//	*************************
	to = t1 + p1;
	std::cout << to << "\n";
	t1 += t2;
	std::cout << t1 << "\n";
	t2 += p1;
	std::cout << t2 << "\n";

//	*************************
	p3 += p1;
	std::cout << p3 << "\n";
	p1 = p2 + t1;
	std::cout << p1 << "\n";
	p2 += t2;
	std::cout << p2 << "\n";

//  *************************
	
	std::vector<Point*> mass;
/*	Point* mass[5];
	mass[0] = new Point(to);
	mass[1] = new P(p1);
	mass[2] = new Point(t1);
	mass[3] = new Point(t2);
	mass[4] = new P(p2);
	*/

	std::cout << "Enter number of objects: ";
	int n;
	std::cin >> n;
	std::cout << "If you need a rectangle, please enter \"Rec\" then enter the coordinates of the central point and sizes.\n";
	std::cout << "If you need a point, please enter \"Point\" then enter the coordinates.\n";
	for (int i = 0; i < n; ++i) {
		std::string fig;
		std::cin >> fig;
		double x0, y0;
		if (fig == "Rec") {
			double a, b;
			std::cin >> x0 >> y0;
			std::cin >> a >> b;
			mass.push_back(new P(x0, y0, a, b));
		}
		else if (fig == "Point") {
			std::cin >> x0 >> y0;
			mass.push_back(new Point(x0, y0));
		}
		else {
			std::cerr << "Incorrect!\n";
			return 0;
		}
	}
	getAns(mass);
    return 0;
}

