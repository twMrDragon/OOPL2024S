#pragma once
#include "MovingObject.h"
class Player:public MovingObject
{
private:
	int invincible = 0;//NO Enemy
	
	int bomb=3;
	int remainingLives=3;
	bool fire = false;//get set
	MovingObject body;
	void updateBodyLaction();
public:
	int power = 0;//get set
	void setLocationF(POINTF location);
	void setLocationF(float x, float y);
	void updateLocationFBySpeed();

	virtual vector<MovingObject> attack() = 0;
	bool isDeath(MovingObject bullet);
	virtual void spellCard() = 0;
	void onInit();

};

