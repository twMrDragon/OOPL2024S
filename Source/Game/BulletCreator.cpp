#include "stdafx.h"
#include "BulletCreator.h"

#define _USE_MATH_DEFINES
#include <math.h>

void BulletCreator::createStage1PinkEnemyBullet(Enemy* enemy, MovingObject* player, vector<EnemyBullet>* bullets) {
	POINTF enemyCenter = enemy->getCenter();

	EnemyBullet bullet;
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

void BulletCreator::createStage2YelloEnemyBullet(Enemy* enemy, MovingObject* player, vector<EnemyBullet>* bullets)
{
	EnemyBullet bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite90.bmp" }, RGB(67, 54, 54));
	bullet.setCenter(enemy->getCenter());
	double aimAngle = enemy->angleToTarget(player);

	for (int i = 0; i < 4; i++)
	{
		POINTF speed = Utils::calculateXYSpeed(aimAngle, 2.0f);
		bullet.setSpeed(speed);
		bullets->push_back(bullet);
		aimAngle += 90;
	}
}

void BulletCreator::createStage2PinkEnemyBullet(Enemy* enemy, MovingObject* player, vector<EnemyBullet>* bullets)
{
	EnemyBullet bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite31.bmp" }, RGB(67, 54, 54));
	bullet.setCenter(enemy->getCenter());

	double aimAngle = enemy->angleToTarget(player);

	for (int i = -3; i < 4; i++)
	{
		double currentAngle = aimAngle + i * 36;
		POINTF speed = Utils::calculateXYSpeed(currentAngle, 1.5f);
		bullet.setSpeed(speed);
		bullets->push_back(bullet);
		speed = Utils::calculateXYSpeed(currentAngle, 2.0f);
		bullet.setSpeed(speed);
		bullets->push_back(bullet);
	}
}
