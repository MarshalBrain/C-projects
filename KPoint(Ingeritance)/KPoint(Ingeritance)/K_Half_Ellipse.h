#pragma once
#include "KShape.h"


class KHalfEllipse : public KShape
{
public:
	KHalfEllipse() : KShape() {};
	KHalfEllipse(KPoint centre_, double high_, double width_, double angle_ = 0) : KShape(centre_, high_, width_, angle_)
	{
		Count();
	}

	void Count();

	double getAngle()
	{
		return angle;
	}

	void Show();

	void MoveTo(KPoint& A);
	
	void Shift(double dx, double dy);

	void Draw(COLORREF colour = RGB(0, 0, 0));

	void Rotate(double angle_);

//private:
	KPoint left, right, down, left_up, right_down;
};

