#pragma once
#include "MovingObject.h"
#include "NumberDisplay.h"
#include "BloodDisplay.h"
#include "EnemyBullet.h"
class Boss : public MovingObject
{
public:
	enum class Action {
		ENTER,
		ATTACK,
		LEAVE
	};

	// getter
	int getCurrentHealth();
	int getMaxHealth();
	int getTimer();
	int getStage2Show();

	// need to override
	virtual void update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea) = 0;
	virtual void onInit(MovingObject playerArea) = 0;
	virtual void show() = 0;
	virtual bool isDead() = 0;
	virtual int getFinishFrame() = 0;

	// show boss
	void showDisplay();

	// make damage to boss
	void hurted(int damaged);

	// add bouns point if have time left
	int getTimeLeft();

protected:
	// member
	float damagedRatio = 1.0f;
	int maxHealth = 10000;
	int currentHealth = 10000;
	int timer = 0;
	int stage2Show = 0;
	int timeLeft = 0;
	size_t frameCounter = 0;
	Action currentAction = Action::ENTER;
	POINTF leaveSpeed = POINTF{ 0.0f,-3.0f };

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
	void fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<EnemyBullet>* enemyBullets);
};

