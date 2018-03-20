// KPointIngeritance.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <cmath>
#include "KPoint.h"
#include "KShape.h"
#include "KFlag.h"
#include "KFlagFilled.h"
#include "K_Half_Ellipse.h"
#include "WinMain.h"


using namespace std;






int main()
{
	/*KPoint A(3,6), B(12, 1);
	KPoint C(5, 4), D(10, 1);
	KFlag flag(C, 6, 8, 45);
	KPoint C(0, 0);
	KFlag flag(C, 6, 8);
	flag.Show();
	KHalfEllipse Ell(C, 6, 8, 90);*/


	WinMain(NULL, NULL, NULL, NULL);
	/*flag.Show();
	flag.Explode(2);
	flag.Show();
	flag.MoveTo(B);
	flag.Show();
	flag.Shift(3, 3);
	flag.Show();
	flag.Rotate(60);
	flag.Show();
    KHalfEllipse M(C, 4, 8);
	M.Show();
	M.Explode(2);
	M.Show();
	M.MoveTo(B);
	M.Show();

	flag.Draw();
*/
	return 0;
}

