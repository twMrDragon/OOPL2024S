#pragma once
#include "../Library/gameutil.h"
using namespace game_framework;
class BloodDisplay
{
private:
	POINT location;
	int width;
	int height;
	CMovingBitmap bloodBitmap;

public:
	// setter
	void setLocation(POINT location);
	void setLocation(int x, int y);
	void setWidth(int width);
	void setHeight(int height);

	// getter
	POINT getLocation();

	//
	void onShow(float ratio);
	void onInit();
};