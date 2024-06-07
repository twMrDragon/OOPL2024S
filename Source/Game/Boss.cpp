#include "stdafx.h"
#include "Boss.h"

int Boss::getHealth()
{
	return this->health;
}

int Boss::getTimer()
{
	return this->timer;
}

int Boss::getStage2Show()
{
	return this->stage2Show;
}

void Boss::countdownTimer()
{
	if (this->timer > 0)
	{
		this->timer -= 1;
	}
}

void Boss::fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<MovingObject>* enemyBullets)
{
	double deltaAngle = 360.0 / n;
	MovingObject bullet;
	bullet.LoadBitmapByString(resource, RGB(67, 54, 54));
	bullet.setCenter(this->getCenter());
	for (int i = 0; i < n; i++)
	{
		double currentAngle = angle + deltaAngle * i;
		float x = (float)cos(currentAngle * M_PI / 180) * speed;
		float y = (float)sin(currentAngle * M_PI / 180) * speed;
		bullet.setSpeed(POINTF{ x,y });
		enemyBullets->push_back(bullet);
	}
}