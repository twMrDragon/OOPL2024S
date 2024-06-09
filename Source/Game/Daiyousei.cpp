#include "stdafx.h"
#include "Daiyousei.h"

void Daiyousei::update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea)
{
	switch (this->currentAction)
	{
	case Action::ENTER:
		if (frameCounter < enterSpeeds.size())
		{
			setSpeed(enterSpeeds[frameCounter]);
			updateLocationFBySpeed();
			this->frameCounter += 1;
		}
		else {
			this->currentAction = Action::ATTACK;
			this->frameCounter = 0;
		}
		break;

	case Action::ATTACK:
		if (frameCounter < this->attackSpeeds.size())
		{
			setSpeed(attackSpeeds[frameCounter]);
			updateLocationFBySpeed();
			this->frameCounter += 1;
		}
		else {
			if (this->flashIndex < this->flashLocationFPosX.size())
			{
				POINTF c1 = this->getLocationF();
				this->setLocationF(POINTF{ flashLocationFPosX[flashIndex], this->getLocationF().y });
				this->flashIndex += 1;
			}
			this->frameCounter = 0;
		}
		countdownTimer();
		attack(player, enemyBullets);
		break;
	case Action::LEAVE:
		break;
	default:
		break;
	}
}

void Daiyousei::onInit(MovingObject playerArea)
{
	this->timer = 960;
	LoadBitmapByString({ "Resources\\Image\\ST\\stg2enm\\Sprite33.bmp" }, RGB(140, 150, 141));
	this->setLocationF(playerArea.getCenter().x - this->GetWidth() / 2.0f, (float)-this->GetHeight());
	this->initDisplay(playerArea);

	// enter
	for (int i = 0; i < 30; i++)
	{
		this->enterSpeeds.push_back(POINTF{ 0.0f,4.5f });
	}

	// attack
	for (int direction : {1, -1, 1, -1})
	{
		for (int i = 0; i < 15; i++)
		{
			this->attackSpeeds.push_back(POINTF{ 0.0f,direction * 1.5f });
		}
		for (int i = 0; i < 15; i++)
		{
			this->attackSpeeds.push_back(POINTF{ 0.0f,-direction * 1.5f });
		}
	}

	// flash
	this->flashLocationFPosX.push_back((float)(playerArea.GetLeft() + playerArea.GetWidth() - this->GetWidth() - 20));
	this->flashLocationFPosX.push_back((float)playerArea.GetLeft() + 100);
	this->flashLocationFPosX.push_back((float)(playerArea.GetLeft() + playerArea.GetWidth() - this->GetWidth() - 50));
	this->flashLocationFPosX.push_back((float)playerArea.GetLeft() + 70);
	this->flashLocationFPosX.push_back((float)playerArea.GetLeft() + 150);
	this->flashLocationFPosX.push_back((float)playerArea.GetLeft() + 20);
}

void Daiyousei::show()
{
	this->ShowBitmap();
}

void Daiyousei::attack(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	fireCircleBullets({ "Resources\\Image\\CM\\etama3\\Sprite87.bmp" }, true, enemyBullets);
}

void Daiyousei::fireCircleBullets(vector<string> resource, bool clockwise, vector<MovingObject>* enemyBullets)
{
	if (this->frameCounter == 60)
		this->fireCenter = this->getCenter();

	if (this->frameCounter > 60 && this->frameCounter <= 108)
	{
		MovingObject bullet;
		bullet.LoadBitmapByString(resource, RGB(67, 54, 54));
		bullet.setCenter(fireCenter);

		double startAngle = 90;
		double deltaAngle = (360 / 48.0) * (clockwise ? 1 : -1);
		int currentStep = this->frameCounter - 60;
		float currentSpeed = 2.5f + 0.05f * currentStep;
		double currentAngle = startAngle + deltaAngle * currentStep;
		POINTF speed = Utils::calculateXYSpeed(currentAngle, currentSpeed);
		bullet.setSpeed(speed);
		enemyBullets->push_back(bullet);
		speed = Utils::calculateXYSpeed(currentAngle, currentSpeed * 1.3f);
		bullet.setSpeed(speed);
		enemyBullets->push_back(bullet);
	}
}

