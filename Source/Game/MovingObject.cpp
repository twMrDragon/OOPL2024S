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

double MovingObject::angleToTarget(MovingObject* target)
{
	return Utils::angleToTarget(this->getCenter(), target->getCenter());
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

void MovingObject::setRangeAnimation(int start, int end, int delay, bool isOneTime)//�O�otoggle
{
	if (!isOneTime) thisIsAnimation = true;
	isOnce = isOneTime;
	delayCount = delay;
	this->start = start;
	this->end = end;
}

void MovingObject::handMadeShow()
{
	//SetTopLeft(200, 400);
	SetAnimation(delayCount, false);

	isAnimation = false;
	ShowBitmap();
	settingBitmapbyShow();
}


void MovingObject::settingBitmapbyShow()
{
	if (thisIsAnimation == true && clock() - last_time >= delayCount) {
		frameIndex += 1;
		last_time = clock();
		if (frameIndex == end + 1 && animationCount > 0) {
			animationCount -= 1;
		}
		if (frameIndex == end + 1 && (isOnce || animationCount == 0)) {
			thisIsAnimation = false;
			isAnimationDone = true;
			frameIndex = end;
			return;
		}
		if (frameIndex == end + 1) {
			frameIndex = start;
		}
	}

}

void MovingObject::startToggleAnimation() {
	frameIndex = start;
	thisIsAnimation = true;
	isAnimationDone = false;
}



void MovingObject::updateLocationFBySpeed()
{
	if (speed.x == 0 && speed.y == 0)
		return;
	this->locationF.x += this->speed.x;
	this->locationF.y += this->speed.y;
	updateCMovingBitmapLocation();
}

MovingObject::MovingObject() :CMovingBitmap()
{
	CoCreateGuid(&guid);
}

void MovingObject::setLocationF(POINTF location)
{
	this->locationF = location;
	updateCMovingBitmapLocation();
}

void MovingObject::setLocationF(float x, float y)
{
	this->locationF.x = x;
	this->locationF.y = y;
	updateCMovingBitmapLocation();
}

void MovingObject::setCenter(POINTF location)
{
	this->locationF.x = location.x - this->GetWidth() / 2.0f;
	this->locationF.y = location.y - this->GetHeight() / 2.0f;
	updateCMovingBitmapLocation();
}

void MovingObject::setCenter(float x, float y)
{
	this->locationF.x = x - this->GetWidth() / 2.0f;
	this->locationF.y = y - this->GetHeight() / 2.0f;
	updateCMovingBitmapLocation();
}

void MovingObject::updateCMovingBitmapLocation() {
	CMovingBitmap::SetTopLeft((int)this->locationF.x, (int)this->locationF.y);
}
