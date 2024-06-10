#include "stdafx.h"
#include "Boss.h"

int Boss::getCurrentHealth()
{
	return this->maxHealth;
}

int Boss::getMaxHealth()
{
	return this->currentHealth;
}

int Boss::getTimer()
{
	return this->timer;
}

int Boss::getStage2Show()
{
	return this->stage2Show;
}

void Boss::initDisplay(MovingObject playerArea)
{
	enemyWordDisplay.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite12.bmp" }, RGB(0, 0, 0));
	enemyWordDisplay.SetTopLeft(playerArea.GetLeft(), playerArea.GetTop());

	stageDisplay.onInit();
	stageDisplay.setXY(enemyWordDisplay.GetLeft() + enemyWordDisplay.GetWidth(), enemyWordDisplay.GetTop());

	countdownDisplay.onInit();
	countdownDisplay.setMinDigit(2);
	countdownDisplay.setXY(playerArea.GetLeft() + playerArea.GetWidth() - 32, playerArea.GetTop());

	bloodDisplay.onInit();
	bloodDisplay.setLocation(enemyWordDisplay.GetLeft() + enemyWordDisplay.GetWidth() + 20, playerArea.GetTop() + 7);
	bloodDisplay.setWidth(countdownDisplay.getX() - bloodDisplay.getLocation().x - 5);
	bloodDisplay.setHeight(4);
}

void Boss::showDisplay()
{
	stageDisplay.showNumber(stage2Show);
	enemyWordDisplay.ShowBitmap();
	countdownDisplay.showNumber(timer / 30);
	bloodDisplay.onShow((float)currentHealth / maxHealth);
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