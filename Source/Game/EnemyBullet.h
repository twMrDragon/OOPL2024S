#pragma once
#include "MovingObject.h"
#include "Player.h"
#include <memory>
class EnemyBullet :public MovingObject
{
public:
	enum  class ActionAfterFinish
	{
		KEEP_GOING,
		AIM_PLAYER
	};

	void update(std::shared_ptr<Player> player);
	void setSpeeds(vector<POINTF> speeds);
	void setAction(ActionAfterFinish action);

private:
	size_t frameCounter = 0;
	vector<POINTF> speeds;
	ActionAfterFinish action = ActionAfterFinish::KEEP_GOING;

};

