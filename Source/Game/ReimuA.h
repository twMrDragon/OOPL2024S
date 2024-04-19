#pragma once
#include "Player.h"
#include <xkeycheck.h>
class ReimuA:public Player
{
private:



public:
	vector<MovingObject> attack() override;
	void spellCard() override;

};

