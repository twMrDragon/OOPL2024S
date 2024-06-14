#pragma once
#include "MovingObject.h"
#include "EnemyBullet.h"
class Enemy :public MovingObject
{
private:
	size_t frameCounter = 0;
	bool hitable = true;
	vector<POINTF> speeds;
	map<size_t, vector<void(*)(Enemy*, MovingObject*, vector<EnemyBullet>*)>> action;
	void updateBySpeeds();
	void callEnemyAction(MovingObject* player, vector<EnemyBullet>* bullets);

public:
	// setter
	void setSpeeds(vector<POINTF> speeds);
	void setAction(map<size_t, vector<void(*)(Enemy*, MovingObject*, vector<EnemyBullet>*)>> action);
	void setHitable(bool hitable);

	// getter
	bool getHitable();

	void update(MovingObject* player, vector<EnemyBullet>* bullets);

};

