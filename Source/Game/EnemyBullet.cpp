#include "stdafx.h"
#include "EnemyBullet.h"

void EnemyBullet::update(std::shared_ptr<Player> player)
{
	if (this->frameCounter < speeds.size())
	{
		this->speed = this->speeds[frameCounter];
		this->frameCounter += 1;
	}
	else {
		if (this->action == ActionAfterFinish::AIM_PLAYER)
		{
			float speed = this->speed.x * this->speed.x + this->speed.y * this->speed.y;
			this->action = ActionAfterFinish::KEEP_GOING;
		}
	}
	this->updateLocationFBySpeed();
}

void EnemyBullet::setSpeeds(vector<POINTF> speeds)
{
	this->speeds = speeds;
}

void EnemyBullet::setAction(ActionAfterFinish action)
{
	this->action = action;
}
