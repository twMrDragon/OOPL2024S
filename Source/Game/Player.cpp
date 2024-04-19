#include "stdafx.h"
#include "Player.h"

void Player::onInit() {
	body.LoadEmptyBitmap(4, 4);
	updateBodyLaction();
}

bool Player::isDeath(MovingObject bullet) {
	if (invincible>0)
	{
		return false;
	}
	return IsOverlap(body, bullet);
}

void Player::updateLocationFBySpeed()
{
	MovingObject::updateLocationFBySpeed();
	updateBodyLaction();
}

void Player::setLocationF(POINTF location)
{
	MovingObject::setLocationF(location);
	updateBodyLaction();
}

void Player::setLocationF(float x, float y)
{
	MovingObject::setLocationF(x,y);
	updateBodyLaction();
}



void Player::updateBodyLaction() {
	body.setLocationF(getCenter().x + body.GetWidth() / 2, getCenter().y + body.GetHeight() / 2);
}

