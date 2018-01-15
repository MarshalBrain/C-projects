#pragma once
#include <iostream>
#include <algorithm>

const double eps = 0.0000000000001;

class Point {
public:
	double x0;
	double y0;
	Point(double, double);
	Point(Point const&);
	Point();
	
	virtual Point& operator += (Point const&);

	Point operator + (Point const&) const&;

	virtual Point* operator + (Point*) const&;

	virtual Point& operator += (Point*);

	virtual bool operator == (Point const&) const;

	virtual bool operator < (Point const&) const;

	virtual bool operator <= (Point const&) const;

	virtual void Print(std::ostream&);

	friend std::ostream& operator << (std::ostream&, Point);
};