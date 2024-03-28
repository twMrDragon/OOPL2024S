#include "stdafx.h"
#include "MovingObject.h"

MovingObject::MovingObject() :CMovingBitmap() {
	//HRESULT h = CoCreateGuid(&(this->guid));
	//if (h != S_OK)
	//	throw exception("generate guid failed");
}

void MovingObject::updateTopLeftBySpeed() {
	if (speed.x == 0 && speed.y == 0)
		return;
	SetTopLeft(GetLeft() + speed.x, GetTop() + speed.y);
}