#pragma once
#include "KPoint.h"
#include <Windows.h>

class KShape : public KPoint
{
public:
	KShape() : centre(), high(0), width(0), angle(0) {};
	KShape(KPoint centre_, double high_ = 0, double width_ = 0, double angle_ = 0) : centre(centre_), high(high_), width(width_), angle(angle_) {};

	virtual void Count() = 0;

	virtual void Draw(COLORREF colour) = 0;

	virtual void Explode(double a);

	virtual void Rotate(KPoint& A_, KPoint const& centre_, double angle_); //rotate A_ about B_ by an angle = angle_

	//virtual void Shift(double dx, double dy);

	void Shift(double dx, double dy, KPoint& A_); // сдвиг точки на dx, dy

	void MoveTo(KPoint& B_);

	void MoveTo(KPoint& A_, KPoint& B_);// переместить точку ј на место B

	void setDC(HDC hdc_)
	{
		hdc = hdc_;
	}
	
protected:
	KPoint centre;
	double high, width, angle;
	HDC hdc;
};