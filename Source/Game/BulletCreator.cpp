#include "stdafx.h"
#include "BulletCreator.h"

#define _USE_MATH_DEFINES
#include <math.h>

void BulletCreator::createStage1PinkEnemyBullet(Enemy enemy, MovingObject* player, vector<MovingObject>* bullets) {
	POINTF enemyCenter = enemy.getCenter();

	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite31.bmp" }, RGB(67, 54, 54));
	bullet.setLocationF(enemyCenter.x - bullet.GetWidth() / 2.0f, enemyCenter.y - bullet.GetHeight() / 2.0f);

	POINTF playerCenter = player->getCenter();
	double deltaAngle = 20;
	double emeny2playerAngle = 180 - atan2(playerCenter.y - enemyCenter.y, enemyCenter.x - playerCenter.x) * 180 / M_PI;
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
