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
			changeNextStage(playerArea);
		}

		break;
	case Action::ATTACK:

		attack(player, enemyBullets);
		if (this->frameCounter < this->attackSpeed.size())
		{
			this->speed = attackSpeed[frameCounter];
			this->updateLocationFBySpeed();
			this->frameCounter += 1;
		}
		else {
			this->frameCounter = 0;
		}

		this->countdownTimer();
		// change next time condition
		if (subStage == 0) {
			if (timer == 0 || currentHealth < maxHealth * 0.3) {
				changeNextStage(playerArea);
			}
		}
		else if (subStage == 1) {
			if (this->timer == 0 || currentHealth == 0) {
				changeNextStage(playerArea);
			}
		}
		else if (subStage == 2) {
			if (this->timer == 0 || currentHealth < maxHealth * 0.4) {
				changeNextStage(playerArea);
			}
		}
		else if (subStage == 3) {
			if (this->timer == 0 || currentHealth < maxHealth * 0.2) {
				changeNextStage(playerArea);
			}
		}
		else if (subStage == 4) {
			if (this->timer == 0)
				changeNextStage(playerArea);
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
	this->stage2Show = 1;
	LoadBitmapByString({ "Resources\\Image\\ST\\stg2enm2\\Sprite130.bmp" }, RGB(254, 254, 254));
	this->setLocationF(playerArea.getCenter().x - this->GetWidth() / 2.0f, (float)-this->GetHeight());
	this->initDisplay(playerArea);

	// enter
	for (int i = 0; i < 50; i++)
		this->enterSpeeds.push_back(POINTF{ 0.0f,3.0f });

	// attack
	// stay
	for (int i = 0; i < 150; i++)
		attackSpeed.push_back(POINTF{ 0.0f,0.0f });
	// move
	for (int i = 0; i < 40; i++)
		attackSpeed.push_back(POINTF{ 3.0f,-2.0f });
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 10);
	for (int i = 0; i < 40; i++)
		attackSpeed.push_back(POINTF{ -1.0f,3.0f });
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 10);
	for (int i = 0; i < 40; i++)
		attackSpeed.push_back(POINTF{ -2.0f,-1.0f });
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 10);

	// stay
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 150);

	// move
	for (int i = 0; i < 40; i++)
		attackSpeed.push_back(POINTF{ -1.0f,-1.0f });
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 10);
	for (int i = 0; i < 40; i++)
		attackSpeed.push_back(POINTF{ -2.0f,-0.5f });
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 10);
	for (int i = 0; i < 40; i++)
		attackSpeed.push_back(POINTF{ 3.0f,1.5f });
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 10);

	// stay
	attackSpeed.insert(attackSpeed.end(), attackSpeed.begin(), attackSpeed.begin() + 150);
}

void Cirno::show()
{
	this->ShowBitmap();
}

bool Cirno::isDead()
{
	return subStage == 4 && currentHealth == 0;
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
	else if (subStage == 2) {
		if (frameCounter % 150 < 120 && frameCounter % 20 == 0) {
			double aimAngle = this->angleToTarget(player);
			fireCircleShpaeNBullets(aimAngle, 11, { "Resources\\Image\\CM\\etama3\\Sprite36.bmp" }, 3.0f, enemyBullets);
			aimAngle += 45;
			fireCircleShpaeNBullets(aimAngle, 8, { "Resources\\Image\\CM\\etama3\\Sprite20.bmp" }, 1.5f, enemyBullets);
		}
	}
	else if (subStage == 3) {
		if (frameCounter % 300 >= 210) {
			if (frameCounter % 30 == 0)
				fireBlueFanShape(player, enemyBullets);
		}
		else if (frameCounter % 300 >= 90 && frameCounter % 300 < 190) {
			if (frameCounter % 5 == 0)
				fireRandomBullet(player, enemyBullets);
		}
	}
	else if (subStage == 4) {
		if (timer % 5 == 0)
			fireBulletBesideBoss(player, enemyBullets);
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

void Cirno::fireRandomBullet(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	vector<string> resources = {
		"Resources\\Image\\CM\\etama3\\Sprite15.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite28.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite27.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite24.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite19.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite32.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite44.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite43.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite39.bmp",
		"Resources\\Image\\CM\\etama3\\Sprite36.bmp"
	};
	double baseAngle = (double)rand() / RAND_MAX * 360;
	double deltaAngle = 360.0 / resources.size();
	for (size_t i = 0; i < resources.size(); i++)
	{
		double currentAngle = baseAngle + deltaAngle * i;
		float currentSpeed = (float)rand() / RAND_MAX * 2 + 2;

		EnemyBullet bullet;
		bullet.LoadBitmapByString({ resources[i] }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());
		POINTF speed = Utils::calculateXYSpeed(currentAngle, currentSpeed);
		vector<POINTF> speeds(210 - frameCounter % 300, speed);
		speeds.insert(speeds.end(), 120, POINTF{ 0.0f,0.0f });
		speeds.push_back(speed);

		bullet.setSpeeds(speeds);
		enemyBullets->push_back(bullet);
	}
}

void Cirno::fireBlueFanShape(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	EnemyBullet bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite36.bmp" }, RGB(67, 54, 54));
	bullet.setCenter(this->getCenter());
	double aimAngle = this->angleToTarget(player);
	double deltaAngle = 15.0;
	for (int j = -2; j < 3; j++)
	{
		double currentAngle = aimAngle + deltaAngle * j;
		float baseSpeed = 2.5f;
		for (int i = 1; i < 4; i++)
		{
			bullet.setSpeed(Utils::calculateXYSpeed(currentAngle, baseSpeed));
			baseSpeed += 0.5f;
			enemyBullets->push_back(bullet);
		}
	}
}

void Cirno::fireBulletBesideBoss(MovingObject* player, vector<EnemyBullet>* enemyBullets)
{
	EnemyBullet bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite52.bmp" }, RGB(67, 54, 54));

	for (int i = 0; i < 6; i++)
	{
		double randomAngle = (double)rand() / RAND_MAX * 360;
		POINTF directtion = Utils::calculateXYSpeed(randomAngle, 10.0f);
		POINTF center = this->getCenter();
		POINTF createCenter = POINTF{ center.x + directtion.x,center.y + directtion.y };
		bullet.setCenter(createCenter);
		bullet.setSpeed(Utils::calculateXYSpeed(randomAngle, 1.5f));
		enemyBullets->push_back(bullet);
	}
}

void Cirno::changeNextStage(MovingObject* playerArea)
{
	if (subStage == 0 && currentAction == Action::ENTER) {
		this->frameCounter = 0;
		this->damagedRatio = 0.8f;
		this->currentAction = Action::ATTACK;
	}
	else if (subStage == 0 && currentAction == Action::ATTACK) {
		this->subStage = 1;
		this->currentHealth = (int)(this->maxHealth * 0.3);
		this->frameCounter = 0;
		this->damagedRatio = 0.2f;
		timeLeft += timer;
		this->timer = 900;
		POINTF targetPoint = POINTF{ playerArea->getCenter().x,playerArea->GetTop() + 100.0f };
		Bezier bezier({ this->getCenter(), targetPoint });
		enterSpeeds = bezier.getEachSpeed(30);
		attackSpeed = vector<POINTF>(180, POINTF{ 0.0f,0.0f });
		currentAction = Action::ENTER;
	}
	else if (subStage == 1 && currentAction == Action::ENTER)
	{
		currentAction = Action::ATTACK;
	}
	else if (subStage == 1 && currentAction == Action::ATTACK) {

		subStage = 2;
		currentHealth = maxHealth;
		frameCounter = 0;
		damagedRatio = 0.6f;
		timeLeft += timer;
		this->timer = 1500;
		stage2Show = 0;
		// attack speed
		attackSpeed = vector<POINTF>(40, POINTF{ 0.5f,-1.0f });
		attackSpeed.insert(attackSpeed.end(), 10, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 40, POINTF{ -1.0f,1.0f });
		attackSpeed.insert(attackSpeed.end(), 10, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 40, POINTF{ -0.5f,-1.0f });
		attackSpeed.insert(attackSpeed.end(), 10, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 40, POINTF{ 1.0f,1.0f });
		attackSpeed.insert(attackSpeed.end(), 10, POINTF{ 0.0f,0.0f });

		currentAction = Action::ATTACK;
	}
	else if (subStage == 2 && currentAction == Action::ATTACK) {
		subStage = 3;
		currentHealth = (int)(maxHealth * 0.4);
		frameCounter = 0;
		damagedRatio = 0.1f;
		timeLeft += timer;
		this->timer = 1200;
		POINTF targetPoint = POINTF{ playerArea->getCenter().x,playerArea->GetTop() + 100.0f };
		Bezier bezier({ this->getCenter(), targetPoint });
		enterSpeeds = bezier.getEachSpeed(30);
		currentAction = Action::ENTER;
	}
	else if (subStage == 3 && currentAction == Action::ENTER) {
		attackSpeed = vector<POINTF>(30, POINTF{ 0.0f,-1.0f });
		attackSpeed.insert(attackSpeed.end(), 60, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ -2.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 1.0f,0.5f });
		attackSpeed.insert(attackSpeed.end(), 60, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ -0.5f,1.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 1.5f,-0.5f });

		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 0.0f,-1.0f });
		attackSpeed.insert(attackSpeed.end(), 60, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 2.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ -1.0f,0.5f });
		attackSpeed.insert(attackSpeed.end(), 60, POINTF{ 0.0f,0.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ 0.5f,1.0f });
		attackSpeed.insert(attackSpeed.end(), 30, POINTF{ -1.5f,-0.5f });

		currentAction = Action::ATTACK;
	}
	else if (subStage == 3 && currentAction == Action::ATTACK) {
		subStage = 4;
		currentHealth = (int)(maxHealth * 0.2);
		frameCounter = 0;
		damagedRatio = 0.1f;
		timeLeft += timer;
		this->timer = 900;
		POINTF targetPoint = POINTF{ playerArea->getCenter().x,playerArea->GetTop() + 100.0f };
		Bezier bezier({ this->getCenter(), targetPoint });
		enterSpeeds = bezier.getEachSpeed(30);
		currentAction = Action::ENTER;
	}
	else if (subStage == 4 && currentAction == Action::ENTER) {
		currentAction = Action::ATTACK;
	}
	else if (subStage == 4 && currentAction == Action::ATTACK) {
		this->currentAction = Action::LEAVE;
	}
}
