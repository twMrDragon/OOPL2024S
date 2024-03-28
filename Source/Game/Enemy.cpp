#include "stdafx.h"
#include "Enemy.h"

void Enemy::setSpeeds(vector<Point> speeds){
	this->speeds = speeds;
}

void Enemy::updateBySpeeds() {
	if (frameCounter < speeds.size()) {
		setSpeed(this->speeds[frameCounter]);
		updateTopLeftBySpeed();
		frameCounter += 1;
	}
	else {
		updateTopLeftBySpeed();
	}
}
