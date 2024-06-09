#include "stdafx.h"
#include "BulletCreator.h"

#define _USE_MATH_DEFINES
#include <math.h>

void BulletCreator::createStage1PinkEnemyBullet(Enemy* enemy, MovingObject* player, vector<MovingObject>* bullets) {
	POINTF enemyCenter = enemy->getCenter();

	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite31.bmp" }, RGB(67, 54, 54));
	bullet.setCenter(enemy->getCenter());

	double deltaAngle = 20;
	double emeny2playerAngle = enemy->angleToTarget(player);
	int speed = 2;
	for (int i = -3; i < 4; i++)
	{
		double currentAngle = emeny2playerAngle + deltaAngle * i;
		float x = (float)cos(currentAngle * M_PI / 180) * speed;
		float y = (float)sin(currentAngle * M_PI / 180) * speed;
		bullet.setSpeed(POINTF{ x,y });
		bullets->push_back(bullet);
	}
}

void BulletCreator::createStage2YelloEnemyBullet(Enemy* enemy, MovingObject* player, vector<MovingObject>* bullets)
{
	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite90.bmp" }, RGB(67, 54, 54));
	bullet.setCenter(enemy->getCenter());
	double randomAngle = rand() / (RAND_MAX + 1.0) * 360;

	for (int i = 0; i < 4; i++)
	{
		POINTF speed = Utils::calculateXYSpeed(randomAngle, 2.0f);
		bullet.setSpeed(speed);
		bullets->push_back(bullet);
		randomAngle += 90;
	}
}
