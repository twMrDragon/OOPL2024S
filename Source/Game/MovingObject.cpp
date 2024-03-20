#include "stdafx.h"
#include "MovingObject.h"

MovingObject::MovingObject() :CMovingBitmap() {

}

void MovingObject::updateTopLeftBySpeed() {
	if (speedX == 0 && speedY == 0)
		return;
	SetTopLeft(GetLeft() + speedX, GetTop() + speedY);
}