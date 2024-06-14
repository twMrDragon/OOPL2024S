#include "stdafx.h"
#include "EnemyBullet.h"

void EnemyBullet::update(std::shared_ptr<Player> player)
{
	if (this->frameCounter < speeds.size())
	{
		this->speed = this->speeds[frameCounter];
	}
	else {
		if (this->action == ActionAfterFinish::AIM_PLAYER)
		{
			double angle = this->angleToTarget(player.get());
			POINTF speed = Utils::calculateXYSpeed(angle, actionSpeed);
			this->speed = speed;
			this->action = ActionAfterFinish::KEEP_GOING;
		}
	}
	this->frameCounter += 1;
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

void EnemyBullet::setActionSpeed(float speed)
{
	this->actionSpeed = speed;
}

bool EnemyBullet::isRemovable()
{
	return this->frameCounter > this->speeds.size() * 2;
}
