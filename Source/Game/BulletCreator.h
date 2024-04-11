#pragma once
#include "MovingObject.h"
#include "Enemy.h"
class BulletCreator
{
public:
	static void createStage1PinkEnemyBullet(Enemy enemy, MovingObject* player, vector<MovingObject>* bullets);
};
