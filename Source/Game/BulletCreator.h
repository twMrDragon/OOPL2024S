#pragma once
#include "MovingObject.h"
#include "Enemy.h"
#include "Utils.h"
class BulletCreator
{
public:
	static void createStage1PinkEnemyBullet(Enemy* enemy, MovingObject* player, vector<EnemyBullet>* bullets);
	static void createStage2YelloEnemyBullet(Enemy* enemy, MovingObject* player, vector<EnemyBullet>* bullets);
	static void createStage2PinkEnemyBullet(Enemy* enemy, MovingObject* player, vector<EnemyBullet>* bullets);
};
