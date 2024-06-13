#pragma once
#include "Boss.h"
#include "Bezier.h"
class Cirno : public Boss
{
public:
	void update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	bool isDead() override;
	int getFinishFrame() override;

private:
	// enter
	vector<POINTF> enterSpeeds;

	// attack
	vector<POINTF> subStage0AttackSpeeds;

	int subStage = 0;

	void attack(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void move();
	// subStage0
	void fireBlueBulletWithBellShape(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	// one of the bullet will aim player after move short time
	void fireCircleBulletWithAimPlayer(MovingObject* player, vector<EnemyBullet>* enemyBullets);

	// subStage1
	void fireYellowBullet(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void fireBlueBulletTrunDirection(MovingObject* player, vector<EnemyBullet>* enemyBullets);


	void changeNextStage();
};

