#pragma once
#include "Boss.h"

#define _USE_MATH_DEFINES
#include <math.h>

class RumiaFirst :public Boss
{
public:
	RumiaFirst();

	void update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	void attack(MovingObject* player, vector<MovingObject>* enemyBullets);


private:
	// enter
	vector<POINTF> enterSpeeds;

	// attack
	// only one stage
	vector<POINTF> attackSpeeds;

	// leave
	vector<POINTF> leaveSpeeds;

	// 招式 1
	// 發射 3 層同色子彈，一層 16 顆
	void fire3LevelBullets(MovingObject* player, vector<string> resource, vector<MovingObject>* enemyBullets);

	// 招式 2
	// 發射 5 種顏色子彈，每種 14 顆
	void fire5ColorBullets(MovingObject* player, vector<MovingObject>* enemyBullets);

	// 招式 3
	// 不同時間發射不同顏色不同形狀子彈
	// 直接呼叫 fireCircleShpaeNBullets
};