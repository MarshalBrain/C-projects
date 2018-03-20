#pragma once
#include <iostream>

class KPoint
{
public:
	KPoint(double _x, double _y) : x(_x), y(_y) {};
	KPoint() : x(0), y(0) {};
	KPoint(KPoint& right) : x(right.x), y(right.y) { };

	friend std::istream& operator>> (std::istream& is, KPoint& D);
	friend std::ostream& operator<< (std::ostream& os, KPoint& D);

	double getX()
	{
		return x;
	}
	
	double getY()
	{
		return y;
	}

	void Set(double x_, double y_);

	double x;
	double y;
};