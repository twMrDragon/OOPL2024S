#pragma once
#include "MovingObject.h"
class Enemy :public MovingObject
{
private:
	size_t frameCounter = 0;
	bool hitable = true;
	vector<POINTF> speeds;
	map<size_t, vector<void(*)(Enemy*, MovingObject*, vector<MovingObject>*)>> action;
	void updateBySpeeds();
	void callEnemyAction(MovingObject* player, vector<MovingObject>* bullets);

public:
	// setter
	void setSpeeds(vector<POINTF> speeds);
	void setAction(map<size_t, vector<void(*)(Enemy*, MovingObject*, vector<MovingObject>*)>> action);
	void setHitable(bool hitable);

	// getter
	bool getHitable();

	void update(MovingObject* player, vector<MovingObject>* bullets);

};

