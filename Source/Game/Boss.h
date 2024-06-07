#pragma once
#include "MovingObject.h"
class Boss : public MovingObject
{
public:
	enum class Action {
		ENTER,
		ATTACK,
		LEAVE
	};

	int getHealth();
	int getTimer();
	int getStage2Show();

	virtual void update(MovingObject* player, vector<MovingObject>* enemyBullets, MovingObject* playerArea) = 0;
	virtual void onInit(MovingObject playerArea) = 0;
	virtual void show() = 0;

protected:
	int health = 0;
	int timer = 0;
	int stage2Show = 0;
	size_t frameCounter = 0;
	Action currentAction = Action::ENTER;

	void countdownTimer();
	// µo®g n ­Ó¤l¼u
	void fireCircleShpaeNBullets(double angle, int n, vector<string> resource, float speed, vector<MovingObject>* enemyBullets);
};

