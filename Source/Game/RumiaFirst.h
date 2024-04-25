#pragma once
#include "Boss.h"

#define _USE_MATH_DEFINES
#include <math.h>

class RumiaFirst :public Boss
{
public:
	RumiaFirst();

	enum class Action
	{
		ENTER,
		ATTACK,
		LEAVE,
	};

	void update(MovingObject player, vector<MovingObject>* bullets) override;
	void onInit(MovingObject playerArea) override;
	void show() override;
	void attack(MovingObject player, vector<MovingObject>* bullets);

	void fireType1Bullet(MovingObject player, vector<MovingObject>* bullets);
	void fireType2Bullet(MovingObject player, vector<MovingObject>* bullets);
	void fireType3Bullet(MovingObject player, vector<MovingObject>* bullets);
	void fireType4Bullet(MovingObject player, vector<MovingObject>* bullets);

private:
	size_t frameCounter = 0;
	Action currentAction = Action::ENTER;
	vector<POINTF> enterSpeeds;
	vector<POINTF> attackSpeeds;
	vector<POINTF> leaveSpeeds;
	bool isAttackLoop = true;
};

