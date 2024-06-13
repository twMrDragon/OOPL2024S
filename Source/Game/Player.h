#pragma once
#include "MovingObject.h"
class Player :public MovingObject
{
protected:
	int invincible = 0;//NO Enemy ³o¬OµL¼Ä´V
	int damage = 0;
	int bomb = 3;
	int power = 0;
	int remainingLives = 3;
	bool fire = false;//get set
	MovingObject hitbox;

	void initHitbox();
	void updateHitboxLocation();

public:
	// need to override
	virtual void onInit() = 0;
	virtual vector<MovingObject> attack() = 0;
	virtual void onShow() = 0;
	virtual void spellCard() = 0;

	// setter
	void setPower(int power);
	void setRemainingLives(int remainingLives);
	void setInvincible(int invincible);

	// getter
	int getPower();
	int getRemainingLives();
	int getInvincible();

	bool isDeath(MovingObject bullet);
	void reduceInvincible();

	// will call parent function, because child class may have some other thing need to move
	void setLocationF(POINTF location);
	void setLocationF(float x, float y);
	void updateLocationFBySpeed();
};

