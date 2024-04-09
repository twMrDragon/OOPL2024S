#pragma once
#include <vector>
#include <string>
#include "MovingObject.h"
#include "Enemy.h"
using namespace std;
class MapData
{
public:
	vector<string> resource;
	COLORREF colorFilter;
	POINTF location;
	vector<POINTF> speeds;
	map<size_t, vector<void(*)(Enemy, MovingObject, vector<MovingObject>*)>> enemyAction;
};
