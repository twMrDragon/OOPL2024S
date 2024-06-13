#pragma once
#include "Player.h"
#include <xkeycheck.h>
class ReimuB :public Player
{
private:

	int firingIntervalRedBullet = 4;//fire CD
	int firingIntervalIceBullet = 8;

	int firingIntervalRedBulletCounter = 0;
	int firingIntervalIceBulletCounter = 0;
	CMovingBitmap ballL;
	CMovingBitmap ballR;
	void showBall();

public:
	void onInit() override;
	vector<MovingObject> attack() override;
	void spellCard() override;
	void onShow() override;
};

