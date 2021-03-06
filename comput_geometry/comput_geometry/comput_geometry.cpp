// comput_geometry.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>
const double eps = 0.00000000001;

double getDistance(double, double, double, double);

int main()
{
	int n;
//	std::cout << "Enter amount of tops: ";
	std::ifstream is("input.txt");
	is >> n;
	std::vector<std::pair<double, double> > top;

	top.resize(n);
//	std::cout << "Enter coordinates of the tops:\n";

	for (int i = 0; i < n; ++i) {
		double x, y;
		is >> x >> y;
		top[i] = std::make_pair(x, y);
	}

	std::cout << "Enter coordinates of the point:\n";

	std::pair<double, double> point;
	std::cin >> point.first >> point.second;

	double X = point.first, Y = point.second;
	int cnt = 0;

	for (int i = 0; i < n; ++i) {
		double X1, X2, Y1, Y2;
		if (i != n - 1) {
			X1 = top[i].first, Y1 = top[i].second;
			X2 = top[i + 1].first, Y2 = top[i + 1].second;
		}
		else {
			X1 = top[i].first, Y1 = top[i].second;
			X2 = top[0].first, Y2 = top[0].second;
		}
		double newY = point.second, newX = (newY - Y1)*(X2 - X1) / (Y2 - Y1) + X1;

		double d1 = getDistance(X1, Y1, newX, newY), d2 = getDistance(X2, Y2, newX, newY), d3 = getDistance(X1, Y1, X2, Y2);
		if (d1 <= d3 && d2 <= d3 && X < newX) {
			if (abs(newY - Y1) > eps && abs(newY - Y2) > eps) ++cnt;
			if (abs(newY - Y1) < eps && Y1 > Y2) ++cnt;
			if (abs(newY - Y2) < eps && Y2 > Y1) ++cnt;
		}
		if (abs((X - X2) / (X1 - X2) - (Y - Y2) / (Y1 - Y2)) < eps) {
			std::cout << "\nPoint lies on the border.\n";
			return 0;
		}
	}

//	std::cout << cnt << "\n";
	if (!(cnt % 2)) std::cout << "\nPoint doesn't lie in the polygon area.\n";
	else std::cout << "\nPoint lies in the polygon area.\n";
    return 0;
}

double getDistance(double X1, double Y1, double X2, double Y2) {
	return sqrt((X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2));
}