#pragma once
#include "KFlag.h"
#include <Windows.h>
class KFlagFilled : public KFlag
{
public:
	KFlagFilled() : KFlag() {};
	KFlagFilled(KPoint centre_, double high_, double width_, double angle_ = 0, COLORREF color_ = NULL) : KFlag(centre_, high_, width_, angle_), color(color_) {};

	void Draw(COLORREF colour = RGB(0, 0 ,0));

private:
	COLORREF color;
 
};

