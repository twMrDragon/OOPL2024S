#pragma once
#include "Boss.h"
#include "Utils.h"
class Daiyousei :public Boss
{

public:
	Daiyousei() = default;

	void update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	void attack(MovingObject* player, vector<MovingObject>* enemyBullets);


private:
	// enter
	vector<POINTF> enterSpeeds;


	// attack
	// move up and loop
	vector<POINTF> attackSpeeds;

	// this boss will flash
	size_t flashIndex = 0;
	vector<float> flashLocationFPosX;

	void fireCircleBullets(vector<string> resource, bool clockwise, vector<MovingObject>* enemyBullets);
	void fireWhiteBullets(MovingObject* player, vector<MovingObject>* enemyBullets);
	POINTF fireCenter;
	enum BulletType {
		GREEN_CIRCLE,
		RED_CIRCLE,
		WHITE_AIM_PLAYER
	};
	vector<BulletType> bulletTypes = { GREEN_CIRCLE,RED_CIRCLE,WHITE_AIM_PLAYER,GREEN_CIRCLE,RED_CIRCLE,WHITE_AIM_PLAYER,GREEN_CIRCLE };
	size_t currentFireBulletIndex = 0;
};