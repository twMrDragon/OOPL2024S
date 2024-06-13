#include "stdafx.h"
#include "Cirno.h"

void Cirno::update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea)
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
			changeNextStage();
		}

		break;
	case Action::ATTACK:

		attack(player, enemyBullets);
		move();
		this->frameCounter += 1;

		this->countdownTimer();
		if (subStage == 0) {
			if (timer == 0 || currentHealth < maxHealth * 0.3) {
				POINTF targetPoint = POINTF{ playerArea->getCenter().x,playerArea->GetTop() + 100.0f };
				Bezier bezier({ this->getCenter(), targetPoint });
				enterSpeeds = bezier.getEachSpeed(30);
				changeNextStage();
			}
		}
		else if (subStage == 1) {
			if (this->timer == 0)
				changeNextStage();
		}

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

bool Cirno::isDead()
{
	return subStage == 1 && currentHealth == 0;
}

int Cirno::getFinishFrame()
{
	return 100000;
}

void Cirno::attack(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (subStage == 0)
	{
		if ((frameCounter / 150) % 2 == 0)
		{
			fireBlueBulletWithBellShape(player, enemyBullets);
		}
		else {
			fireCircleBulletWithAimPlayer(player, enemyBullets);
		}
	}
	else if (subStage == 1) {
		fireBlueBulletTrunDirection(player, enemyBullets);
		fireYellowBullet(player, enemyBullets);
	}
}

void Cirno::move()
{
	if (subStage == 0)
	{
		if (this->frameCounter < this->subStage0AttackSpeeds.size())
		{
			this->speed = subStage0AttackSpeeds[frameCounter];
			this->updateLocationFBySpeed();
		}
		else {
			this->frameCounter = 0;
		}
	}
}

void Cirno::fireBlueBulletWithBellShape(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (this->frameCounter % 50 != 0)
		return;

	EnemyBullet bullet;
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

void Cirno::fireCircleBulletWithAimPlayer(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (frameCounter % 50 == 9 || frameCounter % 50 == 29) {
		double angle = this->angleToTarget(player);
		fireCircleShpaeNBullets(angle, 15, { "Resources\\Image\\CM\\etama3\\Sprite35.bmp" }, 3.0f, enemyBullets);
	}
	else if (frameCounter % 50 == 19) {
		EnemyBullet bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite109.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());
		bullet.setAction(EnemyBullet::ActionAfterFinish::AIM_PLAYER);
		bullet.setActionSpeed(3.0f);

		double aimAngle = this->angleToTarget(player);
		double deltaAngle = 360.0 / 33;
		for (int i = 0; i < 36; i++)
		{
			double currentAngle = aimAngle + i * deltaAngle;
			POINTF speed = Utils::calculateXYSpeed(currentAngle, 3.0f);
			vector<POINTF> speeds(30, speed);
			speeds.insert(speeds.end(), 10, POINTF{ 0.0f,0.0f });
			bullet.setSpeeds(speeds);
			enemyBullets->push_back(bullet);
		}
	}
}

void Cirno::fireYellowBullet(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (frameCounter % 180 == 32 || frameCounter % 180 == 80 || frameCounter % 180 == 128)
	{
		EnemyBullet bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite74.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());

		double aimAngle = this->angleToTarget(player);
		double deltaAngle = 15.0;
		for (int i = -2; i < 3; i++)
		{
			double currentAngle = aimAngle + deltaAngle * i;
			POINTF speed = Utils::calculateXYSpeed(currentAngle, 2.5f);
			bullet.setSpeed(speed);

			enemyBullets->push_back(bullet);
		}
	}
}

void Cirno::fireBlueBulletTrunDirection(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	if (frameCounter % 180 % 16 == 0) {
		EnemyBullet bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite100.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());

		int wave = frameCounter % 180 / 16;
		double angle = -10 + (5.5) * wave;
		for (int i = 1; i > -2; i -= 2)
		{
			for (int j = 0; j < 4; j++) {
				POINTF speed = Utils::calculateXYSpeed(angle, 2.0f + 1.5f * j);
				vector<POINTF> speeds(30, speed);
				speeds.insert(speeds.end(), 10, POINTF{ 0.0f,0.0f });
				speed = Utils::calculateXYSpeed(angle + 90 * i, 2.5f);
				speeds.push_back(speed);
				bullet.setSpeeds(speeds);
				enemyBullets->push_back(bullet);
			}
			angle = 180 - angle;
		}
	}
}

void Cirno::changeNextStage()
{
	if (subStage == 0 && currentAction == Action::ENTER) {
		this->frameCounter = 0;
		this->currentAction = Action::ATTACK;
	}
	else if (subStage == 1 && currentAction == Action::ENTER)
	{
		this->timer = 900;
		currentAction = Action::ATTACK;
	}
	else if (subStage == 0 && currentAction == Action::ATTACK) {
		this->subStage = 1;
		this->currentHealth = (int)(this->maxHealth * 0.3);
		this->frameCounter = 0;
		this->damagedRatio = 0.2f;
		timeLeft += timer;
		currentAction = Action::ENTER;
	}
	else if (subStage == 1 && currentAction == Action::ATTACK) {
		this->currentAction = Action::LEAVE;
	}
}
