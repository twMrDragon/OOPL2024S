#include "stdafx.h"
#include "MovingObject.h"

POINTF MovingObject::getCenter()
{
	float centerX = this->locationF.x + this->GetWidth() / 2.0f;
	float centerY = this->locationF.y + this->GetHeight() / 2.0f;
	return POINTF{ centerX,centerY };
}

bool MovingObject::onLeave(MovingObject target)
{
	map < MovingObject, bool >::iterator iter = touched.find(target);
	bool lastState = iter != touched.end() ? iter->second : false;
	bool currentState = this->IsOverlap(*this, target);
	touched[target] = currentState;
	if (lastState && !currentState)
		return true;
	return false;
}

double MovingObject::angle2Target(MovingObject target)
{
	POINTF fromCenter = this->getCenter();
	POINTF targetCenter = target.getCenter();
	double angle2Target = 180 - atan2(targetCenter.y - fromCenter.y, fromCenter.x - targetCenter.x) * 180 / M_PI;
	return angle2Target;
}

bool MovingObject::operator<(const MovingObject& other) const
{
	WCHAR temp[40];
	StringFromGUID2(this->guid, temp, 40);
	wstring str1(temp);
	StringFromGUID2(other.guid, temp, 40);
	wstring str2(temp);
	int result = (str1).compare((str2));
	return result < 0;
}


void MovingObject::updateLocationFBySpeed()
{
	if (speed.x == 0 && speed.y == 0)
		return;
	this->locationF.x += this->speed.x;
	this->locationF.y += this->speed.y;
	updateCMovingBitmapLocation();
}

MovingObject::MovingObject()
{
	CoCreateGuid(&guid);
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
