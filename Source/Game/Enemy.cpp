#include "stdafx.h"
#include "Enemy.h"

void Enemy::setSpeeds(vector<POINTF> speeds) {
	this->speeds = speeds;
}

void Enemy::setAction(map<size_t, vector<void(*)(Enemy*, MovingObject*, vector<EnemyBullet>*)>> action) {
	this->action = action;
}

void Enemy::setHitable(bool hitable)
{
	this->hitable = hitable;
}

bool Enemy::getHitable()
{
	return this->hitable;
}

void Enemy::update(MovingObject* player, vector<EnemyBullet>* bullets) {
	updateBySpeeds();
	callEnemyAction(player, bullets);
	frameCounter += 1;
}

void Enemy::callEnemyAction(MovingObject* player, vector<EnemyBullet>* bullets) {
	map<size_t, vector<void(*)(Enemy*, MovingObject*, vector<EnemyBullet>*)>>::iterator iter = action.find(frameCounter);
	if (iter != action.end())
	{
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			iter->second[i](this, player, bullets);
		}
	}
}

void Enemy::updateBySpeeds() {
	if (frameCounter < speeds.size()) {
		setSpeed(this->speeds[frameCounter]);
		updateLocationFBySpeed();
	}
	else {
		updateLocationFBySpeed();
	}
}
