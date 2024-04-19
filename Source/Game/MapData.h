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
	map<size_t, vector<void(*)(Enemy, MovingObject*, vector<MovingObject>*)>> enemyAction;

	enum class AIM_TARGET {
		NO,
		PLAYER
	};
	AIM_TARGET aimTarget = MapData::AIM_TARGET::NO;

};
