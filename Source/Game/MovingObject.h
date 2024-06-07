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
	void setCenter(POINTF location);
	void setCenter(float x, float y);

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

	//donglong
	void setRangeAnimation(int start, int end, int delay, bool isOneTime);
	void handMadeShow();
	void startToggleAnimation();

protected:
	POINTF speed{ 0,0 };

private:
	map<MovingObject, bool> touched;
	POINTF locationF{ 0,0 };
	GUID guid;
	int start;
	int end;
	bool thisIsAnimation = false;

	void updateCMovingBitmapLocation();
	void settingBitmapbyShow();

};

