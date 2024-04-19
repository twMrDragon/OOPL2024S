#pragma once
#include "../Library/gameutil.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace game_framework;

class MovingObject :public CMovingBitmap
{
public:
	MovingObject();
	// setter
	void setSpeed(POINTF speed) { this->speed = speed; };
	void setSpeedX(float x) { this->speed.x = x; };
	void setSpeedY(float y) { this->speed.y = y; };
	void setLocationF(POINTF location);
	void setLocationF(float x, float y);

	// getter
	POINTF getSpeed() { return this->speed; };
	float getSpeedX() { return this->speed.x; };
	float getSpeedY() { return this->speed.y; };
	POINTF getLocationF() { return this->locationF; };

	// methon
	void updateLocationFBySpeed();
	POINTF getCenter();
	bool onLeave(MovingObject target);
	double angle2Target(MovingObject target);

	// operate
	bool MovingObject::operator<(const MovingObject& other) const;

private:
	POINTF speed{ 0,0 };
	POINTF locationF{ 0,0 };
	map<MovingObject, bool> touched;
	GUID guid;
	void updateCMovingBitmapLocation();

};

