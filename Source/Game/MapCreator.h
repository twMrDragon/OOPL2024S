#pragma once
#include "MovingObject.h"
#include "Bezier.h"
#include "Enemy.h"
#include "MapData.h"
#include "BulletCreator.h"
#include "Boss.h"
#include "RumiaFirst.h"
#include "RumiaSecond.h"
#include <memory>

class MapCreator
{
public:
	static void onInit(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	static std::shared_ptr<Boss> getCurrentBoss(size_t frame, MovingObject playerArea);

private:
	// stage 1
	static void initStage1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	// 藍色小怪 左上進場 路徑彎曲
	static void initStage1Type1Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 右上進場 路徑彎曲
	static void initStage1Type2Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 中間進場 一次進兩條小怪
	static void initStage1Type3Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 粉色小怪 隨便進場 會發射子彈
	static void initStage1Type4Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 隨便進場
	static void initStage1Type5Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 一次兩條 右上進場 路徑彎曲
	static void initStage1Type6Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 一次兩條 左上進場 路徑彎曲
	static void initStage1Type7Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);

	// stage 2
	static void initStage2(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum);
	// TODO stage 2 敵人 天女散花
	// 白色圓點 黃色飛鏢 天女散花
	static void initStage2Type1Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 尿尿路徑 由左向右撇
	static void initStage2Type2Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
	// 藍色小怪 尿尿路徑 由右向左撇
	static void initStage2Type3Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame);
};

