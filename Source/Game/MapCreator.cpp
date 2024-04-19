#include "stdafx.h"
#include "MapCreator.h"

void MapCreator::init(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	MapCreator::initStage1(playerArea, mapDatum);
	MapCreator::initStage2(playerArea, mapDatum);
}

void MapCreator::initStage1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	MapCreator::initStage1Type1Wave(playerArea, mapDatum, 0);
	MapCreator::initStage1Type2Wave(playerArea, mapDatum, 100);
	MapCreator::initStage1Type3Wave(playerArea, mapDatum, 250);
	MapCreator::initStage1Type4Wave(playerArea, mapDatum, 400);
	MapCreator::initStage1Type5Wave(playerArea, mapDatum, 900);
	MapCreator::initStage1Type6Wave(playerArea, mapDatum, 1100);
	MapCreator::initStage1Type7Wave(playerArea, mapDatum, 1180);
	MapCreator::initStage1Type4Wave(playerArea, mapDatum, 1380);
	MapCreator::initStage1Type7Wave(playerArea, mapDatum, 2000);
	MapCreator::initStage1Type6Wave(playerArea, mapDatum, 2100);
	MapCreator::initStage1Type7Wave(playerArea, mapDatum, 2200);
	MapCreator::initStage1Type6Wave(playerArea, mapDatum, 2300);
}

void MapCreator::initStage1Type1Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// 隔畖
	Bezier straightLine1({ POINTF{0,0},POINTF{0,150} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(60);
	vector<POINTF> wave1 = straightLine1Speeds;
	Bezier curve1({ POINTF{0,0},POINTF{77,50},POINTF{154,-50},POINTF{231,0} });
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	wave1.insert(wave1.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave1.insert(wave1.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));
	int startX = playerArea->GetLeft() + mesaureEnemy.GetWidth() * 3 / 2;
	for (int i = 0; i < 5; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX, (float)-mesaureEnemy.GetHeight() };
		mapData.speeds = wave1;
		(*mapDatum)[startFrame] = { mapData };
		startFrame += 12;
		startX += mesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage1Type2Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// 隔畖
	Bezier straightLine1({ POINTF{0,0},POINTF{0,150} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(60);
	Bezier curve1({ POINTF{0,0},POINTF{ -77,50},POINTF{ -154,-50},POINTF{ -231,0} });
	vector<POINTF> wave2 = straightLine1Speeds;
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	wave2.insert(wave2.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave2.insert(wave2.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int startX = playerArea->GetLeft() + playerArea->GetWidth() - mesaureEnemy.GetWidth() * 5 / 2;
	for (int i = 0; i < 8; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX, (float)-mesaureEnemy.GetHeight() };
		mapData.speeds = wave2;
		(*mapDatum)[startFrame] = { mapData };
		startFrame += 12;
		startX -= mesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage1Type3Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// 隔畖
	Bezier straightLine1({ POINTF{0,0},POINTF{0,220} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(75);
	vector<POINTF> wave31 = straightLine1Speeds;
	vector<POINTF> wave32 = straightLine1Speeds;
	Bezier curve1({ POINTF{0,0},POINTF{ -100,150},POINTF{ -200,30} });
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	Bezier curve2({ POINTF{0,0},POINTF{100,150},POINTF{200,30} });
	vector<POINTF> curve2Speeds = curve2.getEachSpeed(90);
	wave31.insert(wave31.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave32.insert(wave32.end(), curve2Speeds.begin() + 1, curve2Speeds.end());

	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int startX1 = playerArea->GetLeft() + mesaureEnemy.GetWidth();
	int startX2 = playerArea->GetLeft() + playerArea->GetWidth() - mesaureEnemy.GetWidth() * 2;
	for (int i = 0; i < 10; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX1, (float)-mesaureEnemy.GetHeight() };
		mapData.speeds = wave31;
		(*mapDatum)[startFrame] = { mapData };

		mapData.location = POINTF{ (float)startX2, (float)-mesaureEnemy.GetHeight() };
		mapData.speeds = wave32;
		(*mapDatum)[startFrame].push_back(mapData);

		startFrame += 12;
		startX1 += (mesaureEnemy.GetWidth() / 2 - 1);
		startX2 -= (mesaureEnemy.GetWidth() / 2 - 1);
	}
}

void MapCreator::initStage1Type4Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite8.bmp" }, RGB(254, 254, 254));
	Bezier straightLine1({ POINTF{0,0} ,POINTF{0,130} });
	Bezier straightLine2({ POINTF{0,0 }, POINTF{ 0,-130 } });
	Bezier curve1({ POINTF{0,0},POINTF{ -25,60},POINTF{ -50,0} });
	Bezier curve2({ POINTF{0,0},POINTF{25,60},POINTF{50,0} });
	Bezier wait({ POINTF{0,0},POINTF{0,0 } });
	vector<POINTF> straightLine41Speeds = straightLine1.getEachSpeed(40);
	vector<POINTF> straightLine42Speeds = straightLine2.getEachSpeed(40);
	vector<POINTF> curve41Speeds = curve1.getEachSpeed(30);
	vector<POINTF> curve42Speeds = curve2.getEachSpeed(30);
	vector<POINTF> waitSpeeds = wait.getEachSpeed(30);
	vector<POINTF> wave4Left = straightLine41Speeds;
	vector<POINTF> wave4Right = straightLine41Speeds;
	wave4Left.insert(wave4Left.end(), waitSpeeds.begin(), waitSpeeds.end());
	wave4Left.insert(wave4Left.end(), curve41Speeds.begin() + 1, curve41Speeds.end());
	wave4Left.insert(wave4Left.end(), straightLine42Speeds.begin() + 1, straightLine42Speeds.end());
	wave4Right.insert(wave4Right.end(), waitSpeeds.begin(), waitSpeeds.end());
	wave4Right.insert(wave4Right.end(), curve42Speeds.begin() + 1, curve42Speeds.end());
	wave4Right.insert(wave4Right.end(), straightLine42Speeds.begin() + 1, straightLine42Speeds.end());

	vector<POINTF> wave4Points = {
		POINTF{(float)playerArea->GetLeft() + 30,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 150,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 120,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 58,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 16,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 75,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 180,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 60,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 28,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 195,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 15,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 105,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 135,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 70,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 30,(float)-mesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 195,(float)-mesaureEnemy.GetHeight()},
	};
	vector<size_t> wave4DeltaFrame = { 45,39,39,39,34,34,29,29,29,24,24,24,24,24,19,0 };


	for (size_t i = 0; i < wave4Points.size(); i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite8.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = wave4Points[i];

		mapData.enemyAction[40] = { &BulletCreator::createStage1PinkEnemyBullet };

		if (wave4Points[i].x + mesaureEnemy.GetWidth() / 2 > playerArea->GetTop() + playerArea->GetWidth() / 2) {
			mapData.speeds = wave4Right;
		}
		else {
			mapData.speeds = wave4Left;
		}
		(*mapDatum)[startFrame] = { mapData };
		startFrame += wave4DeltaFrame[i];
	}
}

void MapCreator::initStage1Type5Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	vector<POINTF> wave5Points = {
		POINTF{210,(float)-mesaureEnemy.GetHeight()},
		POINTF{290,(float)-mesaureEnemy.GetHeight()},
		POINTF{217,(float)-mesaureEnemy.GetHeight()},
		POINTF{357,(float)-mesaureEnemy.GetHeight()},
		POINTF{160,(float)-mesaureEnemy.GetHeight()},
		POINTF{67,(float)-mesaureEnemy.GetHeight()},
		POINTF{270,(float)-mesaureEnemy.GetHeight()},
		POINTF{100,(float)-mesaureEnemy.GetHeight()},
		POINTF{277,(float)-mesaureEnemy.GetHeight()},
		POINTF{297,(float)-mesaureEnemy.GetHeight()},
		POINTF{177,(float)-mesaureEnemy.GetHeight()},
		POINTF{172,(float)-mesaureEnemy.GetHeight()},
		POINTF{179,(float)-mesaureEnemy.GetHeight()},
		POINTF{62,(float)-mesaureEnemy.GetHeight()},
		POINTF{255,(float)-mesaureEnemy.GetHeight()},
		POINTF{262,(float)-mesaureEnemy.GetHeight()},
		POINTF{152,(float)-mesaureEnemy.GetHeight()},
		POINTF{325,(float)-mesaureEnemy.GetHeight()},
		POINTF{180,(float)-mesaureEnemy.GetHeight()},
	};
	vector<int> wave5MovingHeight = {
		102,102,240,99,240,99,99,240,240,93,99,99,99,240,99,99,99,240,240
	};
	vector<bool> wave5TurnDirection = {
		false,true,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false
	};
	Bezier curve1Right({ POINTF{0,-40},POINTF{0,5},POINTF{-5,0},POINTF{40,0} });
	vector<POINTF> curve1RightSpeeds = curve1Right.getEachSpeed(30);
	curve1RightSpeeds[curve1RightSpeeds.size() - 1].y = 0;
	Bezier curve1Left({ POINTF{0,-40},POINTF{0,5},POINTF{5,0},POINTF{ -40,0} });
	vector<POINTF> curve1LeftSpeeds = curve1Left.getEachSpeed(30);
	curve1LeftSpeeds[curve1LeftSpeeds.size() - 1].y = 0;
	for (size_t i = 0; i < wave5Points.size(); i++)
	{
		vector<POINTF> speeds = {};
		for (int j = 0; j < wave5MovingHeight[i] / 3; j++)
			speeds.push_back(POINTF{ 0, 3 });
		if (wave5TurnDirection[i])
		{
			speeds.insert(speeds.end(), curve1RightSpeeds.begin() + 1, curve1RightSpeeds.end());
		}
		else {
			speeds.insert(speeds.end(), curve1LeftSpeeds.begin() + 1, curve1LeftSpeeds.end());
		}


		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = wave5Points[i];
		mapData.speeds = speeds;
		(*mapDatum)[startFrame] = { mapData };
		startFrame += 6;
	}
}

void MapCreator::initStage1Type6Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	Bezier straightLine1({ POINTF{0,0},POINTF{0,150} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(60);
	Bezier curve1({ POINTF{0,0},POINTF{ -77,50},POINTF{ -154,-50},POINTF{ -231,0} });
	vector<POINTF> wave6 = straightLine1Speeds;
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	wave6.insert(wave6.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave6.insert(wave6.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	int startX = playerArea->GetLeft() + playerArea->GetWidth() - mesaureEnemy.GetWidth() * 5 / 2;
	for (int i = 0; i < 6; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX, (float)-mesaureEnemy.GetHeight() };
		mapData.speeds = wave6;
		(*mapDatum)[startFrame] = { mapData };

		mapData.location.x += 30;
		(*mapDatum)[startFrame].push_back(mapData);

		startFrame += 12;
		startX -= mesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage1Type7Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// 隔畖
	Bezier straightLine1({ POINTF{0,0},POINTF{0,150} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(60);
	vector<POINTF> wave1 = straightLine1Speeds;
	Bezier curve1({ POINTF{0,0},POINTF{77,50},POINTF{154,-50},POINTF{231,0} });
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	wave1.insert(wave1.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave1.insert(wave1.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int startX = playerArea->GetLeft() + mesaureEnemy.GetWidth() * 3 / 2;
	for (int i = 0; i < 8; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX, (float)-mesaureEnemy.GetHeight() };
		mapData.speeds = wave1;
		(*mapDatum)[startFrame] = { mapData };

		mapData.location.x -= 30;
		(*mapDatum)[startFrame].push_back(mapData);

		startFrame += 12;
		startX += mesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage2(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	MapCreator::initStage2Type2Wave(playerArea, mapDatum, 2400);
	MapCreator::initStage2Type3Wave(playerArea, mapDatum, 2680);
	MapCreator::initStage2Type2Wave(playerArea, mapDatum, 2960);
	MapCreator::initStage2Type3Wave(playerArea, mapDatum, 3240);
}

void MapCreator::initStage2Type2Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int startX = playerArea->GetLeft() + mesaureEnemy.GetWidth();

	for (size_t i = 0; i < 17; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX, (float)-mesaureEnemy.GetHeight() };
		mapData.aimTarget = MapData::AIM_TARGET::PLAYER;
		startX += 20;
		(*mapDatum)[startFrame] = { mapData };
		startFrame += 15;
	}
}

void MapCreator::initStage2Type3Wave(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum, int startFrame)
{
	// ノ芠代
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int startX = playerArea->GetLeft() + playerArea->GetWidth() - 2 * mesaureEnemy.GetWidth();

	for (size_t i = 0; i < 17; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)startX, (float)-mesaureEnemy.GetHeight() };
		mapData.aimTarget = MapData::AIM_TARGET::PLAYER;
		startX -= 20;
		(*mapDatum)[startFrame] = { mapData };
		startFrame += 15;
	}
}
