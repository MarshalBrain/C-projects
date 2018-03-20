#include "stdafx.h"
#include "K_Half_Ellipse.h"

	void KHalfEllipse::Count()
	{
		left.Set(centre.x - width / 2, centre.y + high / 2);
		right.Set(centre.x + width / 2, centre.y + high / 2);
		down.Set(centre.x, centre.y - high / 2);
		left_up.Set(left.x, left.y + left.y - down.y);
		right_down.Set(right.x, down.y);
		/*if (angle != 0)
		{
			KHalfEllipse::Rotate(angle);
		}*/
	}

	void KHalfEllipse::Show()
	{
		std::cout << "[Show] centre = " << centre << std::endl;
		std::cout << "[Show] right = " << right << std::endl;
		std::cout << "[Show] left = " << left << std::endl;
		std::cout << "[Show] down = " << down << std::endl;
		std::cout << "________________________________________\n";
		Draw();
	}

	void KHalfEllipse::MoveTo(KPoint& A)
	{
		KShape::MoveTo(centre, A);
		Count();

	}

	void KHalfEllipse::Draw(COLORREF colour)
	{ 
		if (hdc == NULL) throw "Not DC";
	
		double rad = angle * (3.14159265359 / 180);
		XFORM m_xm = { 1,0,0,1, 0, 0 };
		XFORM m_xmE = { 1,0,0,1,0,0 };
		XFORM m_xmM = { 1,0,0,1,0,0 };

		SetGraphicsMode(hdc, GM_ADVANCED);	 // using world coordinate space

		m_xm.eM11 = (FLOAT)cos(rad);
		m_xm.eM12 = (FLOAT)sin(rad);
		m_xm.eM21 = -m_xm.eM12;
		m_xm.eM22 = m_xm.eM11;
		m_xm.eDx = 0;
		m_xm.eDy = 0;

	/*	m_xmM.eM11 = (FLOAT)cos(-rad);
		m_xmM.eM12 = (FLOAT)sin(-rad);
		m_xmM.eM21 = -m_xmM.eM12;
		m_xmM.eM22 = m_xmM.eM11;
		m_xmM.eDx = 0;
		m_xmM.eDy = 0;
*/

		// set of current transform
		SetWorldTransform(hdc, &m_xm);

		KHalfEllipse temp(*this);
		temp.centre.x = centre.x * cos(-rad) - centre.y * sin(-rad);
		temp.centre.y = centre.x * sin(-rad) +  centre.y * cos(-rad);
		temp.Count();


		HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		SelectObject(hdc, hBrush);

		HPEN hp = CreatePen(PS_SOLID, 0.4, colour);
		SelectObject(hdc, hp);


		Chord(hdc, temp.left_up.x*60, temp.left_up.y*60, temp.right_down.x*60, temp.right_down.y*60, temp.right.x*60 , temp.right.y *60, temp.left.x*60 , temp.left.y*60 );
		
		DeleteObject(hBrush);
		// unset of current transform
		SetWorldTransform(hdc, &m_xmE);


	}

	void KHalfEllipse::Rotate(double angle_)
	{
		/*KShape::Rotate(left, centre, angle_);
		KShape::Rotate(right, centre, angle_);
		KShape::Rotate(down, centre, angle_);
		KShape::Rotate(left_up, centre, angle_);
		KShape::Rotate(right_down, centre, angle_);*/
		angle += angle_;
	}

	void KHalfEllipse::Shift(double dx, double dy)
	{
		KShape::Shift(dx, dy, centre);
	}
