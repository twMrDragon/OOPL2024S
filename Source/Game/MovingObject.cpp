#include "stdafx.h"
#include "MovingObject.h"

MovingObject::MovingObject() :CMovingBitmap() {
	//HRESULT h = CoCreateGuid(&(this->guid));
	//if (h != S_OK)
	//	throw exception("generate guid failed");
}

void MovingObject::updateTopLeftBySpeed() {
	if (speedX == 0 && speedY == 0)
		return;
	SetTopLeft(GetLeft() + speedX, GetTop() + speedY);
}