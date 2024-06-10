#include "stdafx.h"
#include "Cirno.h"

void Cirno::update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea)
{
	switch (this->currentAction)
	{
	case Action::ENTER:
		if (this->frameCounter < this->enterSpeeds.size())
		{
			this->speed = enterSpeeds[frameCounter];
			this->updateLocationFBySpeed();
			this->frameCounter += 1;
		}
		else {
			this->frameCounter = 0;
			this->currentAction = Action::ATTACK;
		}
		break;
	case Action::ATTACK:
		if (this->frameCounter < this->subStage0AttackSpeeds.size())
		{
			this->speed = subStage0AttackSpeeds[frameCounter];
			this->updateLocationFBySpeed();
			attack(player, enemyBullets);
			this->frameCounter += 1;
		}
		else {
			this->frameCounter = 0;
		}
		this->countdownTimer();
		if (this->timer == 0)
			this->currentAction = Action::LEAVE;

		break;
	case Action::LEAVE:
		this->speed = leaveSpeed;
		this->updateLocationFBySpeed();
	default:
		break;
	}
}

void Cirno::onInit(MovingObject playerArea)
{
	this->timer = 750;
	LoadBitmapByString({ "Resources\\Image\\ST\\stg2enm2\\Sprite130.bmp" }, RGB(254, 254, 254));
	this->setLocationF(playerArea.getCenter().x - this->GetWidth() / 2.0f, (float)-this->GetHeight());
	this->initDisplay(playerArea);

	// enter
	for (int i = 0; i < 50; i++)
		this->enterSpeeds.push_back(POINTF{ 0.0f,3.0f });

	// attack
	// stay
	for (int i = 0; i < 150; i++)
		subStage0AttackSpeeds.push_back(POINTF{ 0.0f,0.0f });
	// move
	for (int i = 0; i < 40; i++)
		subStage0AttackSpeeds.push_back(POINTF{ 3.0f,-2.0f });
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 10);
	for (int i = 0; i < 40; i++)
		subStage0AttackSpeeds.push_back(POINTF{ -1.0f,3.0f });
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 10);
	for (int i = 0; i < 40; i++)
		subStage0AttackSpeeds.push_back(POINTF{ -2.0f,-1.0f });
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 10);

	// stay
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 150);

	// move
	for (int i = 0; i < 40; i++)
		subStage0AttackSpeeds.push_back(POINTF{ -1.0f,-1.0f });
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 10);
	for (int i = 0; i < 40; i++)
		subStage0AttackSpeeds.push_back(POINTF{ -2.0f,-0.5f });
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 10);
	for (int i = 0; i < 40; i++)
		subStage0AttackSpeeds.push_back(POINTF{ 3.0f,1.5f });
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 10);

	// stay
	subStage0AttackSpeeds.insert(subStage0AttackSpeeds.end(), subStage0AttackSpeeds.begin(), subStage0AttackSpeeds.begin() + 150);
}

void Cirno::show()
{
	this->ShowBitmap();
}

void Cirno::attack(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	if ((frameCounter / 150) % 2 == 0)
	{
		fireBlueBulletWithBellShape(player, enemyBullets);
	}
	else {
		fireCircleBulletWithAimPlayer(player, enemyBullets);
	}

}

void Cirno::fireBlueBulletWithBellShape(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	if (this->frameCounter % 50 != 0)
		return;

	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite100.bmp" }, RGB(67, 54, 54));
	bullet.setCenter(this->getCenter());

	double aimAngle = this->angleToTarget(player);
	double deltaAngle = 3.0;
	float baseSpeed = 2.0f;
	for (int i = 6; i > 0; i--)
	{
		double startAngle = aimAngle - i * deltaAngle;
		for (int j = 0; j < i; j++)
		{
			POINTF speed = Utils::calculateXYSpeed(startAngle + deltaAngle * j * 2, baseSpeed);
			bullet.setSpeed(speed);
			enemyBullets->push_back(bullet);
		}
		baseSpeed *= 1.25f;
	}
}

void Cirno::fireCircleBulletWithAimPlayer(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	if (frameCounter % 50 == 9 || frameCounter % 50 == 29) {
		double angle = this->angleToTarget(player);
		fireCircleShpaeNBullets(angle, 15, { "Resources\\Image\\CM\\etama3\\Sprite35.bmp" }, 3.0f, enemyBullets);
	}
	else {

	}
}
