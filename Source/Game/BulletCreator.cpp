#include "stdafx.h"
#include "BulletCreator.h"

#define _USE_MATH_DEFINES
#include <math.h>

void BulletCreator::createStage1PinkEnemyBullet(Enemy enemy, MovingObject player, vector<MovingObject>* bullets) {
	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite31.bmp" }, RGB(67, 54, 54));
	bullet.setLocationF(enemy.getLocationF().x + (enemy.GetWidth() - bullet.GetWidth()) / 2.0f, enemy.getLocationF().y + (enemy.GetHeight() - bullet.GetHeight()) / 2.0f);
	//float deltaAngle = 10;
	//int speed = 5;
	//for (int i = 0; i < 10; i++)
	//{
	//	float x = (float)cos(deltaAngle * i * M_PI / 180) * speed;
	//	float y = (float)sin(deltaAngle * i * M_PI / 180) * speed;
	//	bullet.setSpeed(POINTF{ x, y });
	//	bullets->push_back(bullet);
	//}
	bullet.setSpeed(POINTF{ 0, 5 });
	bullets->push_back(bullet);
}
