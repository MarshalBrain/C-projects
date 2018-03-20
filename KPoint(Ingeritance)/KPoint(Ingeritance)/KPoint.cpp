#include "stdafx.h"
#include "KPoint.h"
#include <iostream>

	std::istream& operator>> (std::istream& is, KPoint& D)
	{
		is >> D.x >> D.y;
		return is;
	}

	std::ostream& operator<< (std::ostream& os, KPoint& D)
	{
		std::cout << "(" << D.x << ", " << D.y << ")";
		return os;
	}

	void KPoint::Set(double x_, double y_)
	{
		x = x_;
		y = y_;
	}