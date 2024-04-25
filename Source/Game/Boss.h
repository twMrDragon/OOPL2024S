#pragma once
#include "MovingObject.h"
class Boss : public MovingObject
{

private:
	int health = 0;

public:
	int getHealth();
	void setHealth(int health);
	virtual void update(MovingObject player, vector<MovingObject>* bullets) = 0;
	virtual void onInit(MovingObject playerArea) = 0;
	virtual void show() = 0;
	
};

