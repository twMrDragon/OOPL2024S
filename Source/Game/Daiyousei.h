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

	//
	size_t flashIndex = 0;
	vector<float> flashLocationFPosX;

	// leave
	vector<POINTF> leaveSpeeds;

	void fireCircleBullets(vector<string> resource,bool clockwise,vector<MovingObject>* enemyBullets);
	POINTF fireCenter;
};