#pragma once
#include "KShape.h"

class KFlag : public KShape
{
public:
	KFlag() : KShape() {};
	KFlag(KPoint centre_, double high_, double width_, double angle_ = 0) : KShape(centre_, high_, width_, angle_)
	{
		Count();
	}


	void Count(); // calculation points of flag
	
	
	void Shift(double dx, double dy);
	void Rotate(double angle_);

	void Show();

	virtual void Draw(COLORREF colour = RGB(0, 0, 0));

protected:
	KPoint right_up;
	KPoint right_down;
	KPoint left_up;
	KPoint left_down;
	KPoint in_angle;
	KPoint right_centre;
};

