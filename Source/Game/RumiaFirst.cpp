#include "stdafx.h"
#include "RumiaFirst.h"

RumiaFirst::RumiaFirst()
{
}

void RumiaFirst::update(MovingObject player, vector<MovingObject>* bullets)
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
		attack(player, bullets);
		setSpeed(attackSpeeds[frameCounter]);
		updateLocationFBySpeed();
		if (frameCounter < attackSpeeds.size() - 2) {
			frameCounter += 1;
		}
		else {
			frameCounter = 0;
			if (!this->isAttackLoop) {
				this->currentAction = Action::LEAVE;
			}
		}
		break;
	case RumiaFirst::Action::LEAVE:
		setSpeed(leaveSpeeds[frameCounter]);
		if (frameCounter < attackSpeeds.size()) {
			frameCounter += 1;
		}
		break;
	default:
		break;
	}
}

void RumiaFirst::onInit(MovingObject playerArea)
{
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
	for (size_t i = 0; i < xDirection.size(); i++)
	{
		for (size_t j = 0; j < 30; j++)
		{
			this->attackSpeeds.push_back(POINTF{ 0,0 });
		}
		for (size_t j = 0; j < 30; j++)
		{
			this->attackSpeeds.push_back(POINTF{ xDirection[i] * 4.5f,yDirection[i] * 2.5f });
		}
	}

	// leave
}

void RumiaFirst::show()
{
	this->ShowBitmap();
}

void RumiaFirst::attack(MovingObject player, vector<MovingObject>* bullets)
{
	if (this->frameCounter == 15)
	{
		fireType1Bullet(player, bullets);
	}
}

void RumiaFirst::fireType1Bullet(MovingObject player, vector<MovingObject>* bullets)
{
	double startAngle = this->angle2Target(player);
	double dAngle = 360.0 / 16;
	MovingObject bullet;
	vector<float> speeds = { 3.0f,3.4f,3.8f };
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite67.bmp" }, RGB(67, 54, 54));
	bullet.setLocationF(this->getCenter().x - bullet.GetWidth() / 2, this->getCenter().y - bullet.GetHeight() / 2);
	for (size_t i = 0; i < 16; i++)
	{
		double currentAngle = startAngle + dAngle * i;
		float x = (float)cos(currentAngle * M_PI / 180);
		float y = (float)sin(currentAngle * M_PI / 180);


		for (size_t j = 0; j < speeds.size(); j++)
		{
			bullet.setSpeed(POINTF{ x * speeds[j],y * speeds[j] });
			bullets->push_back(bullet);
		}
	}
}
