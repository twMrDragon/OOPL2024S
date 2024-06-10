#pragma once
#include "Boss.h"
class Cirno : public Boss
{
public:
	void update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;

private:
	// enter
	vector<POINTF> enterSpeeds;

	// attack
	vector<POINTF> subStage0AttackSpeeds;

	int subStage = 0;

	void attack(MovingObject* player, vector<MovingObject>* enemyBullets);
	void fireBlueBulletWithBellShape(MovingObject* player, vector<MovingObject>* enemyBullets);
	// one of the bullet will aim player after move short time
	void fireCircleBulletWithAimPlayer(MovingObject* player, vector<MovingObject>* enemyBullets);
};

