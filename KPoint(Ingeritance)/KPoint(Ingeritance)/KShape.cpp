#include "stdafx.h"
#include "KShape.h"
const double rad = 3.14159265358979323846 / 180;



	void KShape::Explode(double a)
	{
		if (a > 0)
		{
			high *= a;
			width *= a;
			Count();
		}
		else
			if (a < 0)
			{
				high /= -a;
				width /= -a;
				Count();
			}
	}

	//void KShape::Shift(double dx, double dy)
	//{
	//	Shift(dx, dy, centre);
	//	Count();
	//}

	void KShape::Shift(double dx, double dy, KPoint& A_) // сдвиг точки на dx, dy
	{
		A_.x += dx;
		A_.y += dy;
	}

	void KShape::MoveTo(KPoint& B_)
	{
		MoveTo(centre, B_); // Move centre to _B
		Count(); // пересчЄт координат точек фигуры
	}

	void KShape::MoveTo(KPoint& A_, KPoint& B_) // переместить точку ј на место B
	{
		A_.x = B_.x;
		A_.y = B_.y;
	}

	void KShape::Rotate(KPoint& A_, KPoint const& centre_, double angle_) //rotate A_ about B_ by an angle = angle_
	{
		double x = A_.x, y = A_.y, x0 = centre.x, y0 = centre.y;

		double sn, cs;
		if ((int)angle_ % 270 == 0) { sn = -1; cs = 0; }
		else 
			if ((int)angle_ % 90 == 0 && (int)angle_ % 180 != 0) { sn = 1; cs = 0; }
				else
				if ((int)angle_ % 180 == 0 && (int)angle_ % 360 != 0) { sn = 0; cs = -1; }
					else 
					 if ((int)angle_ % 360 == 0) { sn = 0; cs = 1; }
					  else
						if ((int)angle_ % 360 == 60) { sn = sqrt(3) / 2; cs = 0.5; }
						 else
						if ((int)angle_ % 360 == 30) { cs = sqrt(3) / 2; sn = 0.5; }
					   	else
					{
						angle_ *= rad;
						sn = sin(angle_);
						cs = cos(angle_);
					}

		double out_x = x0 + ((x - x0) * cs - (y - y0) * sn);
		double out_y = y0 + ((x - x0) * sn + (y - y0) * cs);
		A_.x = out_x;
		A_.y = out_y;
	}