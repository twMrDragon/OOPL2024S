#pragma once
#include "MovingObject.h"
class Enemy :public MovingObject
{
private:
	size_t frameCounter = 0;
	vector<Point> speeds;
	map<size_t, vector<void(*)(Enemy, MovingObject, vector<MovingObject>*)>> action;
	void updateBySpeeds();
	void callEnemyAction(MovingObject player, vector<MovingObject>* bullets);

public:
	void setSpeeds(vector<Point> speeds);
	void setAction(map<size_t, vector<void(*)(Enemy, MovingObject, vector<MovingObject>*)>> action);
	void update(MovingObject player, vector<MovingObject>* bullets);

};

