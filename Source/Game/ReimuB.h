#pragma once
#include "Player.h"
#include <xkeycheck.h>
class ReimuB:public Player
{
private:
	int invincible = 0;//�L�ĴV
	int firingInterval_RedBullet = 4;//fire CD
	int firingInterval_IceBullet = 8;
	
public:


	//showplayer
	void onInit();
	vector<MovingObject> attack() override;
	void spellCard() override;

};

