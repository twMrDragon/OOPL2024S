#pragma once
#include "Boss.h"
#include "Utils.h"
class Daiyousei :public Boss
{

public:
	Daiyousei() = default;

	void update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	bool isDead() override;
	void fixFrame(size_t* gameFrameCounter) override;

private:
	// enter
	vector<POINTF> enterSpeeds;


	// attack
	void attack(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	// move up and loop
	vector<POINTF> attackSpeeds;

	// this boss will flash
	size_t flashIndex = 0;
	vector<float> flashLocationFPosX;

	void fireCircleBullets(vector<string> resource, bool clockwise, vector<EnemyBullet>* enemyBullets);
	void fireWhiteBullets(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	POINTF fireCenter;
	enum BulletType {
		GREEN_CIRCLE,
		RED_CIRCLE,
		WHITE_AIM_PLAYER
	};
	vector<BulletType> bulletTypes = { GREEN_CIRCLE,RED_CIRCLE,WHITE_AIM_PLAYER,GREEN_CIRCLE,RED_CIRCLE,WHITE_AIM_PLAYER,GREEN_CIRCLE };
	size_t currentFireBulletIndex = 0;
};