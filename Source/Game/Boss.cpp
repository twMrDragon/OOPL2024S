#include "stdafx.h"
#include "Boss.h"

int Boss::getHealth()
{
	return this->health;
}

int Boss::getTimer()
{
	return this->timer;
}

void Boss::setHealth(int health)
{
	this->health = health;
}

void Boss::setTimer(int timer)
{
	this->timer = timer;
}

void Boss::countdownTimer()
{
	if (this->timer > 0)
	{
		this->timer -= 1;
	}
}
