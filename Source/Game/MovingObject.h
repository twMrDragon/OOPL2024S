#pragma once

#include "../Library/gameutil.h"
using namespace game_framework;

class MovingObject :public CMovingBitmap
{
public:
	MovingObject();
	// setter
	void setSpeedX(int speed) { speedX = speed; };
	void setSpeedY(int speed) { speedY = speed; };
	void setSpeed(int x, int y) { speedX = x; speedY = y; };

	// getter
	int getSpeedX() { return speedX; };
	int getSpeedY() { return speedY; };

	// methon
	void updateTopLeftBySpeed();
private:
	int speedX = 0;
	int speedY = 0;
};

