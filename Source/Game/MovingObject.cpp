#include "stdafx.h"
#include "MovingObject.h"

void MovingObject::updateLocationFBySpeed()
{
	if (speed.x == 0 && speed.y == 0)
		return;
	this->locationF.x += this->speed.x;
	this->locationF.y += this->speed.y;
	updateCMovingBitmapLocation();
}

void MovingObject::setLocationF(POINTF location)
{
	this->locationF = locationF;
	updateCMovingBitmapLocation();
}

void MovingObject::setLocationF(float x, float y)
{
	this->locationF.x = x;
	this->locationF.y = y;
	updateCMovingBitmapLocation();
}

void MovingObject::updateCMovingBitmapLocation() {
	CMovingBitmap::SetTopLeft((int)this->locationF.x, (int)this->locationF.y);
}
