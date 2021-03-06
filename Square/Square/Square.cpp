// Square.cpp: определяет точку входа для консольного приложения.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

const double eps = 0.00000001;

double getArea(std::vector<std::pair<double, double> >&);

void insertPoint(std::vector<std::pair<double, double> >&, std::pair<double, double>);

int main()
{
	int n;
	std::cout << "Enter amount of tops: ";
	std::cin >> n;
	std::cout << "\nCoordinates\nX Y\n";
	
	std::vector<std::pair<double, double> > top;
	top.resize(n);

	for (int i = 0; i < n; ++i) {
		int x, y;
		std::cin >> x >> y;
		top[i] = std::make_pair(x, y);
 	}

	double mainArea = getArea(top);
	std::pair<double, double> point;
	std::cout << "\nEnter coordinates of necessary point: ";
	std::cin >> point.first >> point.second;

	insertPoint(top, point);

	double newArea = getArea(top);

	if (abs(newArea - mainArea) < eps) {
		std::cout << "\nThe Point lies on the side of the polygon.";
		return 0;
	}
	
	if (mainArea > newArea) std::cout << "\nThe Point lies inside the polygon.";
	if (mainArea < newArea) std::cout << "\nThe Point lies outside the polygon.";

    return 0;
}

double getArea(std::vector<std::pair<double, double> >& top) {
	//The Gauss's area formula is used

	int n = top.size();
	double S = 0;

	for (int i = 0; i < n - 1; ++i) 
		S += top[i].first * top[i + 1].second - top[i + 1].first * top[i].second;
	S += top[n - 1].first * top[0].second - top[0].first * top[n - 1].second;
	S = abs(S) / (double)2;

	return S;
}

void insertPoint(std::vector<std::pair<double, double> >& top, std::pair<double, double> point) {
	int n = top.size(),k = 0;
	double minDis = sqrt((top[0].first - point.first) * (top[0].first - point.first) + (top[0].second - point.second) * (top[0].second - point.second));
	for (int i = 1; i < n; ++i) {
		double distance = sqrt((top[i].first - point.first) * (top[i].first - point.first) + (top[i].second - point.second) * (top[i].second - point.second));
		if (minDis > distance) {
			k = i;
			minDis = distance;
		}
	}
	top.insert(top.begin() + k, point);
}