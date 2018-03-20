#include "stdafx.h"
#include "KFlag.h"
#include <Windows.h>
	
	void KFlag::Count() // calculation points of flag
	{
		right_up.Set(centre.x + width / 2, centre.y + high / 2);
		right_down.Set(centre.x + width / 2, centre.y - high / 2);
		left_up.Set(centre.x - width / 2, centre.y + high / 2);
		left_down.Set(centre.x - width / 2, centre.y - high / 2);
		in_angle.Set(centre.x - (width / 2 - high / 2), centre.y);
		right_centre.Set(right_down.x, in_angle.y);
	}


	void KFlag::Draw(COLORREF colour)
	{
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

		// Изменяем текущее преобразование
		SetWorldTransform(hdc, &m_xm);

		KFlag temp(*this);
		temp.centre.x = round(centre.x * cos(-rad) - centre.y * sin(-rad));
		temp.centre.y = round(centre.x * sin(-rad) + centre.y * cos(-rad));
		temp.Count();

		std::cout << "\nTEMP: ";
		temp.Show();

		//set colour of pen
		/*HPEN hp = CreatePen(PS_SOLID, 0.1, colour);
		SelectObject(hdc,hp);
*/
		MoveToEx(hdc, temp.right_down.x*60, temp.right_down.y*60, NULL);
		LineTo(hdc, temp.right_up.x*60, temp.right_up.y*60);
		LineTo(hdc, temp.left_up.x*60, temp.left_up.y*60);
		LineTo(hdc, temp.in_angle.x*60, temp.in_angle.y*60);
		LineTo(hdc, temp.left_down.x*60, temp.left_down.y*60);
		LineTo(hdc, temp.right_down.x*60, temp.right_down.y*60);

		/*MoveToEx(hdc, right_down.x*60, right_down.y*60, NULL);
		LineTo(hdc, right_up.x*60, right_up.y*60);
		LineTo(hdc, left_up.x*60, left_up.y*60);
		LineTo(hdc, in_angle.x*60, in_angle.y*60);
		LineTo(hdc, left_down.x*60, left_down.y*60);
		LineTo(hdc, right_down.x*60, right_down.y*60);*/


		SetWorldTransform(hdc, &m_xmE);
	}


	void KFlag::Shift(double dx, double dy)
	{
		KShape::Shift(dx, dy, centre);
	    Count();
	}
	

	void KFlag::Rotate(double angle_)
	{
		/*KShape::Rotate(right_up, centre, angle_);
		KShape::Rotate(right_down, centre, angle_);
		KShape::Rotate(left_up, centre, angle_);
		KShape::Rotate(left_down, centre, angle_);
		KShape::Rotate(in_angle, centre, angle_);
		KShape::Rotate(right_centre, centre, angle_);*/
		angle += angle_;
	}

	void KFlag::Show()
	{
		std::cout << "[Show] centre = " << centre << std::endl;
		std::cout << "[Show] right_up = " << right_up << std::endl;
		std::cout << "[Show] right_down = " << right_down << std::endl;
		std::cout << "[Show] left_up = " << left_up << std::endl;
		std::cout << "[Show] left_down = " << left_down << std::endl;
		std::cout << "[Show] in_angle = " << in_angle << std::endl;
		std::cout << "_________________________________\n";
	}
