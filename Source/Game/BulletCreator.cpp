#include "stdafx.h"
#include "BulletCreator.h"

void BulletCreator::createStage1PinkEnemyBullet(Enemy enemy, MovingObject player, vector<MovingObject>* bullets) {
	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite31.bmp" }, RGB(67, 54, 54));
	bullet.SetTopLeft(enemy.GetLeft() + (enemy.GetWidth() - bullet.GetWidth()) / 2, enemy.GetTop() + (enemy.GetHeight() - bullet.GetHeight()) / 2);
	bullet.setSpeed(Point(0, 5));
	bullets->push_back(bullet);
}
