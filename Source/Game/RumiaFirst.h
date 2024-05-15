#pragma once
#include "Boss.h"

#define _USE_MATH_DEFINES
#include <math.h>

class RumiaFirst :public Boss
{
public:
	RumiaFirst();

	enum class Action
	{
		ENTER,
		ATTACK,
		LEAVE,
	};

	void update(MovingObject player, vector<MovingObject>* enemyBullets) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	void attack(MovingObject player, vector<MovingObject>* enemyBullets);

private:
	size_t frameCounter = 0;

	Action currentAction = Action::ENTER;
	vector<POINTF> enterSpeeds;
	vector<POINTF> attackSpeeds;
	vector<POINTF> leaveSpeeds;

	// 發射 n 個子彈
	void fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<MovingObject>* enemyBullets);

	// 招式 1
	// 發射 3 層同色子彈，一層 16 顆
	void fire3LevelBullets(MovingObject player, vector<string> resource, vector<MovingObject>* enemyBullets);

	// 招式 2
	// 發射 5 種顏色子彈，每種 14 顆
	void fire5ColorBullets(MovingObject player, vector<MovingObject>* enemyBullets);

	// 招式 3
	// 不同時間發射不同顏色不同形狀子彈
	// 直接呼叫 fireCircleShpaeNBullets
};