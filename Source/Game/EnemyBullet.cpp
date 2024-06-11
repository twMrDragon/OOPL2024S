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
			float noDirectionSpeed = sqrtf(this->speed.x * this->speed.x + this->speed.y * this->speed.y);
			double angle = this->angleToTarget(player.get());
			POINTF speed = Utils::calculateXYSpeed(angle, noDirectionSpeed);
			this->speed = speed;
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
