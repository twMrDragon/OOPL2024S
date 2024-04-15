#pragma once
#include "MovingObject.h"
#include "Bezier.h"
#include "Enemy.h"
#include "MapData.h"
#include "BulletCreator.h"

class MapCreator
{
public:
	static void init(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);

private:
	// stage 1
	static void initStage1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave2(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave3(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave4(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave5(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave6(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static void initStage1Wave7(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);

	// stage 2
};

