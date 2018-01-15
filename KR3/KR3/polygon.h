#pragma once
#include "Point.h"

class P : public Point {
public:
	double a;
	double b;
	P(double, double, double, double);
	P(P const&);
	P();
	P& operator += (P const&);

	P& operator += (Point const&);

	P operator + (P const&) const&;

	P operator + (Point const&) const&;

	void Print(std::ostream&);

	friend std::ostream& operator << (std::ostream&, P&);

	bool operator == (P const&) const&;

	bool operator < (P const&) const&;

	bool operator <= (P const&) const&;

};