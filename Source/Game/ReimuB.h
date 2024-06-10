#pragma once
#include "Player.h"
#include <xkeycheck.h>
class ReimuB:public Player
{
private:
	
	int firingIntervalRedBullet = 4;//fire CD
	int firingIntervalIceBullet = 8;

	int firingIntervalRedBulletCounter = 0;
	int firingIntervalIceBulletCounter = 0;
	CMovingBitmap ballL;
	CMovingBitmap ballR;
	
public:

	void showBall();
	//showplayer
	void onInit();
	vector<MovingObject> attack() override;
	void spellCard() override;

};

