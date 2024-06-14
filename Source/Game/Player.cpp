#include "stdafx.h"
#include "Player.h"

bool Player::isDeath(MovingObject bullet) {
	if (invincible > 0)
	{
		return false;
	}
	return IsOverlap(hitbox, bullet);
}

void Player::reduceInvincible() {
	if (invincible > 0)
	{
		invincible--;
	}
}

void Player::updateLocationFBySpeed()
{
	MovingObject::updateLocationFBySpeed();
	updateHitboxLocation();
}

void Player::setLocationF(POINTF location)
{
	MovingObject::setLocationF(location);
	updateHitboxLocation();
}

void Player::setLocationF(float x, float y)
{
	MovingObject::setLocationF(x, y);
	updateHitboxLocation();
}

void Player::initHitbox()
{
	hitbox.LoadEmptyBitmap(4, 4);
}

void Player::updateHitboxLocation()
{
	hitbox.setCenter(this->getCenter());
}

void Player::setPower(int power) {
	this->power = power;
}

int Player::getPower() {
	return this->power;
}

void Player::setRemainingLives(int remainingLives) {
	this->remainingLives = remainingLives;
}

int Player::getRemainingLives() {
	return this->remainingLives;
}

int Player::getInvincible() {
	return this->invincible;
}

void Player::setHP(int HealthPoints)
{
	this->HP = HealthPoints;
}

int Player::getHP()
{
	return this->HP;
}

void Player::setInvincible(int invincible) {
	this->invincible = invincible;
}