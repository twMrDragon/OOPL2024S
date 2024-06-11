#include "stdafx.h"
#include "Daiyousei.h"

void Daiyousei::update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea)
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
			this->fireCenter = this->getCenter();
			this->frameCounter = 0;
			this->currentAction = Action::ATTACK;
		}
		break;

	case Action::ATTACK:
		if (this->timer == 0)
		{
			this->frameCounter = 0;
			this->currentAction = Action::LEAVE;
		}
		if (frameCounter < this->attackSpeeds.size())
		{
			setSpeed(attackSpeeds[frameCounter]);
			updateLocationFBySpeed();
			this->frameCounter += 1;
		}
		else {
			if (this->flashIndex < this->flashLocationFPosX.size())
			{
				this->setLocationF(POINTF{ flashLocationFPosX[flashIndex], this->getLocationF().y });
				this->fireCenter = this->getCenter();
				this->flashIndex += 1;
			}
			this->frameCounter = 0;
		}
		countdownTimer();
		attack(player, enemyBullets);
		break;
	case Action::LEAVE:
		this->speed = this->leaveSpeed;
		this->updateLocationFBySpeed();
		break;
	default:
		break;
	}
}

void Daiyousei::onInit(MovingObject playerArea)
{
	this->timer = 900;
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

void Daiyousei::attack(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (currentFireBulletIndex < bulletTypes.size() - 1 && frameCounter == attackSpeeds.size())
	{
		currentFireBulletIndex += 1;
	}
	else {
		switch (bulletTypes[currentFireBulletIndex])
		{
		case GREEN_CIRCLE:
			fireCircleBullets({ "Resources\\Image\\CM\\etama3\\Sprite87.bmp" }, true, enemyBullets);
			break;
		case RED_CIRCLE:
			fireCircleBullets({ "Resources\\Image\\CM\\etama3\\Sprite79.bmp" }, false, enemyBullets);
			break;
		case WHITE_AIM_PLAYER:
			fireWhiteBullets(player, enemyBullets);
			break;
		default:
			break;
		}
	}

}

void Daiyousei::fireCircleBullets(vector<string> resource, bool clockwise, vector<EnemyBullet>* enemyBullets)
{
	if (this->frameCounter > 60 && this->frameCounter <= 108)
	{
		EnemyBullet bullet;
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

void Daiyousei::fireWhiteBullets(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (this->frameCounter > 30 && this->frameCounter <= 110)
	{
		if (frameCounter % 5 == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				EnemyBullet bullet;
				bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite109.bmp" }, RGB(67, 54, 54));
				bullet.setCenter(fireCenter);

				double angle = Utils::angleToTarget(fireCenter, player->getCenter()) + 30 * (i - 1);
				POINTF speed = Utils::calculateXYSpeed(angle, 3.0f);
				bullet.setSpeed(speed);

				enemyBullets->push_back(bullet);
			}
		}
	}
}
