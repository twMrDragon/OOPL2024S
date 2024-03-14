#pragma once

#include "../Library/gameutil.h"
using namespace game_framework;

class MovingObject :public CMovingBitmap
{
public:
	MovingObject();
	int getSpeedX() { return speedX; };
	void setSpeedX(int speed) { speedX = speed; };
	int getSpeedY() { return speedY; };
	void setSpeedY(int speed) { speedY = speed; };
	void updateTopLeftBySpeed();
private:
	int speedX = 0;
	int speedY = 0;
};

