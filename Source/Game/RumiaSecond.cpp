#include "stdafx.h"
#include "RumiaSecond.h"

void RumiaSecond::subStageEnter()
{
	// 判斷當前要的什麼速度
	vector<vector<POINTF>*> enterSpeedSelector = {
		&subStage0EnterSpeeds,
		&subStage1EnterSpeeds
	};

	vector<POINTF>* currentEnterSpeeds = (enterSpeedSelector[subStage]);

	// 更新
	if (this->frameCounter < currentEnterSpeeds->size())
	{
		this->setSpeed((*currentEnterSpeeds)[frameCounter]);
		this->updateLocationFBySpeed();
		this->frameCounter += 1;
	}
	else {
		// 切換到 attack
		vector<int> frameCounterSelector = {
			SUBSTAGE_0_MOVE_FRAME + SUBSTAGE_0_WAIT_FRAME,
			0
		};
		this->currentAction = Action::ATTACK;
		this->frameCounter = frameCounterSelector[subStage];
	}
}

void RumiaSecond::subStage0Moving()
{
	// generate speed
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + SUBSTAGE_0_WAIT_FRAME) {
		// move to center
		if (this->subStage0IsLeave) {
			for (int i = 0; i < SUBSTAGE_0_MOVE_FRAME; i++)
			{
				this->subStage0AttackSpeeds[i].x = -this->subStage0AttackSpeeds[i].x;
				this->subStage0AttackSpeeds[i].y = -this->subStage0AttackSpeeds[i].y;
			}
		}
		// leave center
		else {
			double randomAngle = rand() / (RAND_MAX + 1.0) * 180 + 180;

			POINTF speed = Utils::calculateXYSpeed(randomAngle, 2.5f);
			for (int i = 0; i < SUBSTAGE_0_MOVE_FRAME; i++)
			{
				this->subStage0AttackSpeeds[i] = speed;
			}
		}
		this->subStage0IsLeave = !this->subStage0IsLeave;
	}
	else {
		this->speed = this->subStage0AttackSpeeds[this->frameCounter];
		this->updateLocationFBySpeed();
	}
}

void RumiaSecond::subStage0Attack(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	// 變換攻擊方式
	if (frameCounter == SUBSTAGE_0_MOVE_FRAME + SUBSTAGE_0_WAIT_FRAME) {
		this->subStage0FireWayIndex = rand() % SUBSTAGE_0_ATTACK_WAY_COUNT;
	}
	// 執行攻擊方式
	else {
		if (this->subStage0FireWayIndex == 0)
		{
			fireRedLine(player, enemyBullets);
		}
		else if (this->subStage0FireWayIndex == 1) {
			fireGreenCurve(player, enemyBullets);
		}
		else if (this->subStage0FireWayIndex == 2) {
			fireBlueCircle(player, enemyBullets);
		}
		else if (this->subStage0FireWayIndex == 3) {
			fireBlueCircleWith3RedLine(player, enemyBullets);
		}
	};
}

void RumiaSecond::fireRedLine(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	// 18 to 30 frame
	// 移動時就會發射
	if (this->frameCounter % 2 == 0 && this->frameCounter >= 18 && this->frameCounter <= 30) {
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite64.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());

		double angle = this->angleToTarget(player);
		for (int i = 0; i < 10; i++)
		{
			POINTF speed = Utils::calculateXYSpeed(angle, 2.5f + 0.2f * i);
			bullet.setSpeed(speed);
			enemyBullets->push_back(bullet);
		}
	}
}

void RumiaSecond::fireGreenCurve(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	// 總共 16 顆
	// 移動時就會發射
	if (frameCounter >= 2 && frameCounter <= 17)
	{
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite71.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());

		double angle = this->angleToTarget(player) + (frameCounter - 6.0) * 6;
		POINTF speed = Utils::calculateXYSpeed(angle, 2.0f + 0.1f * frameCounter);
		bullet.setSpeed(speed);

		enemyBullets->push_back(bullet);
	}
}

void RumiaSecond::fireBlueCircle(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	// 大顆有 4 波 12 顆
	// 小顆有 3 波 16 顆
	double angle = this->angleToTarget(player);
	// 大
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME)
	{
		this->fireCircleShpaeNBullets(angle, 12, { "Resources\\Image\\CM\\etama3\\Sprite68.bmp" }, 4.0f, enemyBullets);
	}
	// 小
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 2) {
		this->fireCircleShpaeNBullets(angle, 16, { "Resources\\Image\\CM\\etama3\\Sprite20.bmp" }, 3.2f, enemyBullets);
	}
	// 小
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 10) {
		this->fireCircleShpaeNBullets(angle, 16, { "Resources\\Image\\CM\\etama3\\Sprite20.bmp" }, 3.3f, enemyBullets);
	}
	// 大
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 11) {
		this->fireCircleShpaeNBullets(angle, 12, { "Resources\\Image\\CM\\etama3\\Sprite68.bmp" }, 3.2f, enemyBullets);
	}
	// 大
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 14) {
		this->fireCircleShpaeNBullets(angle, 12, { "Resources\\Image\\CM\\etama3\\Sprite68.bmp" }, 3.8f, enemyBullets);
	}
	// 小
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 17) {
		this->fireCircleShpaeNBullets(angle, 16, { "Resources\\Image\\CM\\etama3\\Sprite20.bmp" }, 3.8f, enemyBullets);
	}
	// 大
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 20) {
		this->fireCircleShpaeNBullets(angle, 12, { "Resources\\Image\\CM\\etama3\\Sprite68.bmp" }, 3.8f, enemyBullets);
	}
}

void RumiaSecond::fireBlueCircleWith3RedLine(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	double angle = this->angleToTarget(player);
	// 三道 16 顆紅色子彈
	if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 10)
	{
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite47.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());

		int deltaAngle = 4;
		for (int i = -deltaAngle; i < deltaAngle + 1; i += deltaAngle)
		{
			double currentAngle = angle + i;
			for (int j = 0; j < 16; j++)
			{
				POINTF speed = Utils::calculateXYSpeed(currentAngle, 2.0f + j * 0.2f);
				bullet.setSpeed(speed);
				enemyBullets->push_back(bullet);
			}
		}
	}
	// 藍色 16 顆子彈
	else if (this->frameCounter == SUBSTAGE_0_MOVE_FRAME + 15)
	{
		this->fireCircleShpaeNBullets(angle, 16, { "Resources\\Image\\CM\\etama3\\Sprite68.bmp" }, 3.0f, enemyBullets);
	}
}

void RumiaSecond::fireBlueHalfCircle(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	// from angle 45 to 180
	// and angle 45 to 225
	if (
		(frameCounter >= 0 && frameCounter < 16) ||
		(frameCounter >= 34 && frameCounter < 50) ||
		(frameCounter >= 68 && frameCounter < 84) ||
		(frameCounter >= 102 && frameCounter < 118)) {

		double swipeAngle = 0.0;
		if ((frameCounter >= 0 && frameCounter < 16) ||
			(frameCounter >= 68 && frameCounter < 84))
			swipeAngle = 135.0;
		else
			swipeAngle = 180.0;

		double angle = 45.0 + (swipeAngle / 16) * (frameCounter % 17);
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite36.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());
		POINTF speed = Utils::calculateXYSpeed(angle, 2.5f + 0.2f * (frameCounter % 17));
		bullet.setSpeed(speed);
		enemyBullets->push_back(bullet);
	}

	if (
		(frameCounter >= 17 && frameCounter < 33) ||
		(frameCounter >= 51 && frameCounter < 67) ||
		(frameCounter >= 85 && frameCounter < 101) ||
		(frameCounter >= 119 && frameCounter < 135)) {

		double swipeAngle = 0.0;
		if ((frameCounter >= 17 && frameCounter < 33) ||
			(frameCounter >= 85 && frameCounter < 101))
			swipeAngle = -135.0;
		else
			swipeAngle = -180.0;

		double angle = 135.0 + (swipeAngle / 16) * (frameCounter % 17);
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite37.bmp" }, RGB(67, 54, 54));
		bullet.setCenter(this->getCenter());
		POINTF speed = Utils::calculateXYSpeed(angle, 2.5f + 0.2f * (frameCounter % 17));
		bullet.setSpeed(speed);
		enemyBullets->push_back(bullet);
	}
}

void RumiaSecond::fireLightBlueHalfCircle(MovingObject* player, vector<MovingObject>* enemyBullets)
{
}

void RumiaSecond::subStage1Attack(MovingObject* player, vector<MovingObject>* enemyBullets)
{
	fireBlueHalfCircle(player, enemyBullets);
}

void RumiaSecond::subStage1Moving()
{
	int increasingTimer = (timer - 720) * -1;
	int movingStage = increasingTimer / 180;
	int movingSubStage = (increasingTimer % 180);
	if (movingSubStage == 0) {
		if (movingStage == 0)
			this->speed = POINTF{ 0,0 };
		else if (movingStage == 1)
			this->speed = Utils::calculateXYSpeed(210, 2.5f);
		else if (movingStage == 2 || movingStage == 3)
			this->speed = Utils::calculateXYSpeed(30, 2.5f);
	}
	if (movingSubStage < SUBSTAGE_1_MOVE_FRAME) {
		this->updateLocationFBySpeed();
	}
}

void RumiaSecond::update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea)
{
	switch (this->currentAction)
	{
	case Action::ENTER:
		subStageEnter();
		break;
	case Action::ATTACK:
		switch (subStage)
		{
		case 0:
			if (timer == 0)
			{
				// change to sub-stage 1
				this->currentAction = Action::ENTER;
				this->frameCounter = 0;
				this->subStage = 1;
				this->timer = 30 * 24 + 1;
				POINTF targetPointf{ playerArea->getCenter().x,playerArea->GetTop() + 100.0f };
				Bezier bezier({ this->getCenter(), targetPointf });
				this->subStage1EnterSpeeds = bezier.getEachSpeed(30);
				break;
			}
			subStage0Moving();
			subStage0Attack(player, enemyBullets);
			if (frameCounter == SUBSTAGE_0_MOVE_FRAME + SUBSTAGE_0_WAIT_FRAME)
				frameCounter = 0;
			else
				frameCounter += 1;
			break;
		case 1:
			if (timer == 0) {
				this->currentAction = Action::LEAVE;
				this->speed = POINTF{ 0.0f, -2.0f };
				break;
			}
			subStage1Moving();
			subStage1Attack(playerArea, enemyBullets);
			if (frameCounter == SUBSTAGE_1_MOVE_FRAME + SUBSTAGE_1_WAIT_FRAME)
				frameCounter = 0;
			else
				frameCounter += 1;
			break;
		default:
			break;
		}
		this->countdownTimer();
		break;
	case Action::LEAVE:
		this->speed = this->leaveSpeed;
		this->updateLocationFBySpeed();
		break;
	default:
		break;
	}
}

void RumiaSecond::onInit(MovingObject playerArea)
{
	// character setting
	this->timer = 1050;
	//this->timer = 30;
	this->stage2Show = 1;
	LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm2\\Sprite132.bmp" }, RGB(142, 142, 142));
	this->setLocationF(playerArea.getCenter().x - this->GetWidth() / 2.0f, (float)(playerArea.GetTop() - this->GetHeight()));

	initDisplay(playerArea);

	//enter action
	for (int i = 0; i < 40; i++)
	{
		this->subStage0EnterSpeeds.push_back(POINTF{ 0,3 });
	}
	for (int i = 0; i < 10; i++)
	{
		this->subStage0EnterSpeeds.push_back(POINTF{ 0,0 });
	}

	// attack action
	// substage 0
	for (int i = 0; i < SUBSTAGE_0_MOVE_FRAME + SUBSTAGE_0_WAIT_FRAME; i++)
	{
		this->subStage0AttackSpeeds.push_back(POINTF{ 0,0 });
	}

	// substage 1
	// substage 2
	// substage 3
	// substage 4
	// substage 5

	// leave action
}

void RumiaSecond::show()
{
	this->ShowBitmap();
}