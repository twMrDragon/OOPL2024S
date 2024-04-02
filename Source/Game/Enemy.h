#pragma once
#include "MovingObject.h"
class Enemy:public MovingObject
{
private:
	size_t frameCounter = 0;
	vector<Point> speeds;

public:
	void setSpeeds(vector<Point> speeds);
	void updateBySpeeds();
};

