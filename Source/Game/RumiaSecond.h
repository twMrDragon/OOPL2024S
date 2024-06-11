#pragma once
#include "Boss.h"
#include "Bezier.h"
#include "Utils.h"
#include <time.h>
#define SUBSTAGE_0_MOVE_FRAME 30
#define SUBSTAGE_0_WAIT_FRAME 30
#define SUBSTAGE_0_ATTACK_WAY_COUNT 4

#define SUBSTAGE_1_MOVE_FRAME 30
#define SUBSTAGE_1_WAIT_FRAME 150

class RumiaSecond :public Boss
{
private:
	// enter
	void subStageEnter();
	vector<POINTF> subStage0EnterSpeeds;
	vector<POINTF> subStage1EnterSpeeds;

	// attack
	// substage 0, ��� stage 1
	vector<POINTF> subStage0AttackSpeeds;
	bool subStage0IsLeave = false;
	void subStage0Moving();
	void subStage0Attack(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	int subStage0FireWayIndex = 0;
	void fireRedLine(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void fireGreenCurve(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void fireBlueCircle(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void fireBlueCircleWith3RedLine(MovingObject* player, vector<EnemyBullet>* enemyBullets);

	// substage 1, ��� stage 1, �ݦ嶥�q
	vector<POINTF> subStage1AttackSpeeds;
	void fireBlueHalfCircle(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void fireLightBlueHalfCircle(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void subStage1Attack(MovingObject* player, vector<EnemyBullet>* enemyBullets);
	void subStage1Moving();

	// substage 2, ��� stage 0
	vector<POINTF> stage2AttackSpeeds;
	// substage 3, ��� stage 0 �ݦ嶥�q

	int subStage = 0;


public:
	void update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
};