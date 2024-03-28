#pragma once

#include "../Library/gameutil.h"
#include "Point.h"
using namespace game_framework;

class MovingObject :public CMovingBitmap
{
public:
	MovingObject();
	// setter
	void setSpeed(Point speed) { this->speed = speed; };
	void setSpeedX(int x) { this->speed.x = x; };
	void setSpeedY(int y) { this->speed.y = y; };

	// getter
	Point getSpeed() { return this->speed; };
	int getSpeedX() { return this->speed.x; };
	int getSpeedY() { return this->speed.y; };

	// methon
	void updateTopLeftBySpeed();
private:
	Point speed;
};

