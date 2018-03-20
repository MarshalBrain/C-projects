#include "stdafx.h"
#include "KFlagFilled.h"

void KFlagFilled::Draw(COLORREF colour)
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

	KFlagFilled temp(*this);
	temp.centre.x = round(centre.x * cos(-rad) - centre.y * sin(-rad));
	temp.centre.y = round(centre.x * sin(-rad) + centre.y * cos(-rad));
	temp.Count();
	

	POINT poly[4] = { {temp.right_down.getX()*60, temp.right_down.getY()*60}, {temp.left_down.getX()*60, temp.left_down.getY()*60},
	{temp.in_angle.getX()*60, temp.in_angle.getY()*60}, {temp.right_centre.getX()*60, temp.right_centre.getY()*60 } };

	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);

	Polygon(hdc, poly, 4);
	DeleteObject(hBrush);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	POINT poly1[4] = { { temp.in_angle.getX()*60 , temp.in_angle.getY()*60  }, {temp.left_up.getX()*60, temp.left_up.getY()*60} , {temp.right_up.getX()*60, temp.right_up.getY()*60},
	{ temp.right_centre.getX()*60 , temp.right_centre.getY()*60  } };

	Polygon(hdc, poly1, 4);


	SetWorldTransform(hdc, &m_xmE);

}
