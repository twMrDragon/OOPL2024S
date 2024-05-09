#include "stdafx.h"
#include "RumiaFirst.h"

RumiaFirst::RumiaFirst()
{
}

void RumiaFirst::update(MovingObject player, vector<MovingObject>* enemyBullets)
{
	switch (this->currentAction)
	{
	case RumiaFirst::Action::ENTER:
		setSpeed(enterSpeeds[frameCounter]);
		updateLocationFBySpeed();
		if (frameCounter < enterSpeeds.size() - 2) {
			frameCounter += 1;
		}
		else {
			this->currentAction = Action::ATTACK;
			frameCounter = 0;
		}
		break;
	case RumiaFirst::Action::ATTACK:
		attack(player, enemyBullets);
		setSpeed(attackSpeeds[frameCounter]);
		updateLocationFBySpeed();
		if (frameCounter < attackSpeeds.size() - 2) {
			frameCounter += 1;
		}
		else {
			frameCounter = 0;
		}
		countdownTimer();
		if (this->getTimer() == 0)
		{
			// change to leave action
			this->currentAction = Action::LEAVE;
			enemyBullets->clear();
			frameCounter = 0;
		}
		break;
	case RumiaFirst::Action::LEAVE:
		if (frameCounter < leaveSpeeds.size())
		{
			this->setSpeed(leaveSpeeds[frameCounter]);
			frameCounter += 1;
		}
		updateLocationFBySpeed();
		break;
	default:
		break;
	}
}

void RumiaFirst::onInit(MovingObject playerArea)
{
	this->setTimer(740);
	LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm2\\Sprite132.bmp" }, RGB(142, 142, 142));
	this->setLocationF(playerArea.getCenter().x - this->GetWidth() / 2.0f, (float)-this->getHealth());

	// enter
	for (size_t i = 0; i < 30; i++)
	{
		this->enterSpeeds.push_back(POINTF{ 4.5f,4 });
	}

	// attack
	vector<int> xDirection = { -1,-1,1,1 };
	vector<int> yDirection = { -1,1,-1,1 };
	vector<size_t> waitFrame = { 60,60,60,60 };
	for (size_t i = 0; i < xDirection.size(); i++)
	{
		for (size_t j = 0; j < waitFrame[i]; j++)
		{
			this->attackSpeeds.push_back(POINTF{ 0,0 });
		}
		for (size_t j = 0; j < 30; j++)
		{
			this->attackSpeeds.push_back(POINTF{ xDirection[i] * 4.5f,yDirection[i] * 2.5f });
		}
	}

	// leave
	for (int i = 0; i < 10; i++)
	{
		this->leaveSpeeds.push_back(POINTF{ 0,0 });
	}
	this->leaveSpeeds.push_back(POINTF{ -3,-3 });
}

void RumiaFirst::show()
{
	this->ShowBitmap();
}

void RumiaFirst::attack(MovingObject player, vector<MovingObject>* enemyBullets)
{
	// 招式 1 (紅色)
	if (this->frameCounter == 355)
	{
		fire3LevelBullets(player, { "Resources\\Image\\CM\\etama3\\Sprite63.bmp" }, enemyBullets);
	}
	// 招式 1(藍色)
	else if (this->frameCounter == 10)
	{
		fire3LevelBullets(player, { "Resources\\Image\\CM\\etama3\\Sprite67.bmp" }, enemyBullets);
	}
	// 招式 2
	else if (this->frameCounter == 120)
	{
		fire5ColorBullets(player, enemyBullets);
	}
	// 招式 1(綠色)
	else if (this->frameCounter == 175)
	{
		fire3LevelBullets(player, { "Resources\\Image\\CM\\etama3\\Sprite71.bmp" }, enemyBullets);
	}
	// 招式 1(黃色)
	else if (this->frameCounter == 190)
	{
		fire3LevelBullets(player, { "Resources\\Image\\CM\\etama3\\Sprite74.bmp" }, enemyBullets);
	}
	// 招式 3
	else if (this->frameCounter == 280)
	{
		double angle = this->angle2Target(player);
		fireCircleShpaeNBullets(angle, 8, { "Resources\\Image\\CM\\etama3\\Sprite51.bmp" }, 4.0f, enemyBullets);
		fireCircleShpaeNBullets(angle + 360 / 16.0, 8, { "Resources\\Image\\CM\\etama3\\Sprite19.bmp" }, 4.6f, enemyBullets);
	}
	else if (this->frameCounter == 285) {
		double angle = this->angle2Target(player);
		fireCircleShpaeNBullets(angle - 20, 8, { "Resources\\Image\\CM\\etama3\\Sprite47.bmp" }, 3.8f, enemyBullets);
		fireCircleShpaeNBullets(angle + 5, 8, { "Resources\\Image\\CM\\etama3\\Sprite15.bmp" }, 4.4f, enemyBullets);
	}
	else if (this->frameCounter == 290) {
		double angle = this->angle2Target(player);
		fireCircleShpaeNBullets(angle + 5, 8, { "Resources\\Image\\CM\\etama3\\Sprite55.bmp" }, 3.8f, enemyBullets);
		fireCircleShpaeNBullets(angle + 10, 8, { "Resources\\Image\\CM\\etama3\\Sprite23.bmp" }, 4.2f, enemyBullets);
	}
	else if (this->frameCounter == 295) {
		double angle = this->angle2Target(player);
		fireCircleShpaeNBullets(angle - 2, 8, { "Resources\\Image\\CM\\etama3\\Sprite58.bmp" }, 5.6f, enemyBullets);
		fireCircleShpaeNBullets(angle - 4, 8, { "Resources\\Image\\CM\\etama3\\Sprite26.bmp" }, 3.8f, enemyBullets);
	}
	else if (this->frameCounter == 300) {
		double angle = this->angle2Target(player);
		fireCircleShpaeNBullets(angle + 10, 8, { "Resources\\Image\\CM\\etama3\\Sprite60.bmp" }, 4.2f, enemyBullets);
		fireCircleShpaeNBullets(angle + 30, 8, { "Resources\\Image\\CM\\etama3\\Sprite28.bmp" }, 3.8f, enemyBullets);
	}
}

void RumiaFirst::fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<MovingObject>* enemyBullets)
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

void RumiaFirst::fire3LevelBullets(MovingObject player, vector<string> resource, vector<MovingObject>* enemyBullets)
{
	double angle = this->angle2Target(player);
	fireCircleShpaeNBullets(angle, 16, resource, 3.8f, enemyBullets);
	fireCircleShpaeNBullets(angle, 16, resource, 3.4f, enemyBullets);
	fireCircleShpaeNBullets(angle, 16, resource, 3.0f, enemyBullets);
}

void RumiaFirst::fire5ColorBullets(MovingObject player, vector<MovingObject>* enemyBullets)
{
	double angle = this->angle2Target(player);
	fireCircleShpaeNBullets(angle, 14, { "Resources\\Image\\CM\\etama3\\Sprite137.bmp" }, 4.6f, enemyBullets);
	fireCircleShpaeNBullets(angle + 4, 14, { "Resources\\Image\\CM\\etama3\\Sprite136.bmp" }, 4.2f, enemyBullets);
	fireCircleShpaeNBullets(angle + 8, 14, { "Resources\\Image\\CM\\etama3\\Sprite138.bmp" }, 3.8f, enemyBullets);
	fireCircleShpaeNBullets(angle + 12, 14, { "Resources\\Image\\CM\\etama3\\Sprite139.bmp" }, 3.4f, enemyBullets);
	fireCircleShpaeNBullets(angle + 16, 14, { "Resources\\Image\\CM\\etama3\\Sprite135.bmp" }, 3.0f, enemyBullets);
}