#pragma once
#include "Boss.h"
#include "EnemyBullet.h"

#define _USE_MATH_DEFINES
#include <math.h>

class RumiaFirst :public Boss
{
public:
	RumiaFirst();

	void update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	void attack(MovingObject* player, vector<EnemyBullet>* enemyBullets);


private:
	// enter
	vector<POINTF> enterSpeeds;

	// attack
	// only one stage
	vector<POINTF> attackSpeeds;

	// �ۦ� 1
	// �o�g 3 �h�P��l�u�A�@�h 16 ��
	void fire3LevelBullets(MovingObject* player, vector<string> resource, vector<EnemyBullet>* enemyBullets);

	// �ۦ� 2
	// �o�g 5 ���C��l�u�A�C�� 14 ��
	void fire5ColorBullets(MovingObject* player, vector<EnemyBullet>* enemyBullets);

	// �ۦ� 3
	// ���P�ɶ��o�g���P�C�⤣�P�Ϊ��l�u
	// �����I�s fireCircleShpaeNBullets
};