#pragma once
#include "MovingObject.h"
#include "NumberDisplay.h"
#include "BloodDisplay.h"
class Boss : public MovingObject
{
public:
	enum class Action {
		ENTER,
		ATTACK,
		LEAVE
	};

	int getCurrentHealth();
	int getMaxHealth();
	int getTimer();
	int getStage2Show();

	virtual void update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea) = 0;
	virtual void onInit(MovingObject playerArea) = 0;
	virtual void show() = 0;

	void showDisplay();

protected:
	// member
	float demagedRatio = 1.0f;
	int maxHealth = 10000;
	int currentHealth = 10000;
	int timer = 0;
	int stage2Show = 0;
	size_t frameCounter = 0;
	Action currentAction = Action::ENTER;

	// for display boss detail
	// ���� enemy �r
	CMovingBitmap enemyWordDisplay;
	// enemy �r�Ǫ��Ʀr
	NumberDisplay stageDisplay;
	// �˼ƭp��
	NumberDisplay countdownDisplay;
	// ��q
	BloodDisplay bloodDisplay;

	void initDisplay(MovingObject playerArea);
	

	void countdownTimer();
	// �o�g n �Ӥl�u
	void fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<MovingObject>* enemyBullets);
};

