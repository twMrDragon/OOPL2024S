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

	int getCurrentHealth();
	int getMaxHealth();
	int getTimer();
	int getStage2Show();

	virtual void update(MovingObject* player, vector<EnemyBullet>* enemyBullets, MovingObject* playerArea) = 0;
	virtual void onInit(MovingObject playerArea) = 0;
	virtual void show() = 0;
	virtual bool isDead() = 0;
	virtual void fixFrame(size_t* gameFrameCounter) = 0;

	void showDisplay();

	void hurted(int damaged);

protected:
	// member
	float damagedRatio = 1.0f;
	int maxHealth = 10000;
	int currentHealth = 10000;
	int timer = 0;
	int stage2Show = 0;
	size_t frameCounter = 0;
	Action currentAction = Action::ENTER;
	POINTF leaveSpeed = POINTF{ 0.0f,-3.0f };

	// for display boss detail
	// 黃色 enemy 字
	CMovingBitmap enemyWordDisplay;
	// enemy 字旁的數字
	NumberDisplay stageDisplay;
	// 倒數計時
	NumberDisplay countdownDisplay;
	// 血量
	BloodDisplay bloodDisplay;

	void initDisplay(MovingObject playerArea);


	void countdownTimer();
	// 發射 n 個子彈
	void fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<EnemyBullet>* enemyBullets);
};

