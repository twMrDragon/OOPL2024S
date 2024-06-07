#pragma once
#include "MovingObject.h"
class Player:public MovingObject
{
private:
	int invincible = 0;//NO Enemy ³o¬OµL¼Ä´V
	int damage = 0;
	int bomb=3;
	int remainingLives=3;
	bool fire = false;//get set
	MovingObject body;
	void updateBodyLaction();
	int power = 0;//get set
public:
	void onInit();
	void setPower(int power);
	int getPower();
	void setRemainingLives(int remainingLives);
	int getRemainingLives();
	void setInvincible(int invincible);
	int getInvincible();//player show


	virtual vector<MovingObject> attack() = 0;
	bool isDeath(MovingObject bullet);
	void reduceInvincible();

	virtual void spellCard() = 0;

	void setLocationF(POINTF location);
	void setLocationF(float x, float y);
	void updateLocationFBySpeed();
};

