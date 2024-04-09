#include "stdafx.h"
#include "Enemy.h"

void Enemy::setSpeeds(vector<Point> speeds) {
	this->speeds = speeds;
}

void Enemy::setAction(map<size_t, vector<void(*)(Enemy, MovingObject, vector<MovingObject>*)>> action) {
	this->action = action;
}

void Enemy::update(MovingObject player, vector<MovingObject>* bullets) {
	updateBySpeeds();
	callEnemyAction(player, bullets);
	frameCounter += 1;
}

void Enemy::callEnemyAction(MovingObject player, vector<MovingObject>* bullets) {
	map<size_t, vector<void(*)(Enemy, MovingObject, vector<MovingObject>*)>>::iterator iter = action.find(frameCounter);
	if (iter != action.end())
	{
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			iter->second[i](*this, player, bullets);
		}
	}
}

void Enemy::updateBySpeeds() {
	if (frameCounter < speeds.size()) {
		setSpeed(this->speeds[frameCounter]);
		updateTopLeftBySpeed();
	}
	else {
		updateTopLeftBySpeed();
	}
}
