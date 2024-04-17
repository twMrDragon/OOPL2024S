#include "stdafx.h"
#include "MapCreator.h"

void MapCreator::init(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	MapCreator::initStage1(playerArea, mapDatum);
}

void MapCreator::initStage1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	MapCreator::initStage1Wave1(playerArea, mapDatum);
	MapCreator::initStage1Wave2(playerArea, mapDatum);
	MapCreator::initStage1Wave3(playerArea, mapDatum);
	MapCreator::initStage1Wave4(playerArea, mapDatum);
	MapCreator::initStage1Wave5(playerArea, mapDatum);
	MapCreator::initStage1Wave6(playerArea, mapDatum);
	MapCreator::initStage1Wave7(playerArea, mapDatum);
}

void MapCreator::initStage1Wave1(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
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
	Enemy wave1MesaureEnemy;
	wave1MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));
	int frame = 0;
	int wave1X = playerArea->GetLeft() + wave1MesaureEnemy.GetWidth() * 3 / 2;
	for (int i = 0; i < 5; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave1X, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave1;
		(*mapDatum)[frame] = { mapData };
		frame += 12;
		wave1X += wave1MesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage1Wave2(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
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
	Enemy wave2MesaureEnemy;
	wave2MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int frame = 100;
	int wave2X = playerArea->GetLeft() + playerArea->GetWidth() - wave2MesaureEnemy.GetWidth() * 5 / 2;
	for (int i = 0; i < 8; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave2X, (float)-wave2MesaureEnemy.GetHeight() };
		mapData.speeds = wave2;
		(*mapDatum)[frame] = { mapData };
		frame += 12;
		wave2X -= wave2MesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage1Wave3(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
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
	Enemy wave3MesaureEnemy;
	wave3MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int frame = 250;
	int wave3X1 = playerArea->GetLeft() + wave3MesaureEnemy.GetWidth();
	int wave3X2 = playerArea->GetLeft() + playerArea->GetWidth() - wave3MesaureEnemy.GetWidth() * 2;
	for (int i = 0; i < 10; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave3X1, (float)-wave3MesaureEnemy.GetHeight() };
		mapData.speeds = wave31;
		(*mapDatum)[frame] = { mapData };

		mapData.location = POINTF{ (float)wave3X2, (float)-wave3MesaureEnemy.GetHeight() };
		mapData.speeds = wave32;
		(*mapDatum)[frame].push_back(mapData);

		frame += 12;
		wave3X1 += (wave3MesaureEnemy.GetWidth() / 2 - 1);
		wave3X2 -= (wave3MesaureEnemy.GetWidth() / 2 - 1);
	}
}

void MapCreator::initStage1Wave4(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	int frame = 400;
	Enemy wave4MesaureEnemy;
	wave4MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite8.bmp" }, RGB(254, 254, 254));
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
		POINTF{(float)playerArea->GetLeft() + 30,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 150,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 120,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 58,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 16,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 75,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 180,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 60,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 28,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 195,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 15,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 105,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 135,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 70,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + 30,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea->GetLeft() + playerArea->GetWidth() - 195,(float)-wave4MesaureEnemy.GetHeight()},
	};
	vector<size_t> wave4DeltaFrame = { 45,39,39,39,34,34,29,29,29,24,24,24,24,24,19,0 };


	for (size_t i = 0; i < wave4Points.size(); i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite8.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = wave4Points[i];

		mapData.enemyAction[40] = { &BulletCreator::createStage1PinkEnemyBullet };

		if (wave4Points[i].x + wave4MesaureEnemy.GetWidth() / 2 > playerArea->GetTop() + playerArea->GetWidth() / 2) {
			mapData.speeds = wave4Right;
		}
		else {
			mapData.speeds = wave4Left;
		}
		(*mapDatum)[frame] = { mapData };
		frame += wave4DeltaFrame[i];
	}
}

void MapCreator::initStage1Wave5(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	// ノ芠代
	Enemy wave5MesaureEnemy;
	wave5MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int frame = 900;
	vector<POINTF> wave5Points = {
		POINTF{210,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{290,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{217,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{357,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{160,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{67,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{270,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{100,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{277,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{297,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{177,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{172,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{179,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{62,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{255,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{262,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{152,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{325,(float)-wave5MesaureEnemy.GetHeight()},
		POINTF{180,(float)-wave5MesaureEnemy.GetHeight()},
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
		(*mapDatum)[frame] = { mapData };
		frame += 6;
	}
}

void MapCreator::initStage1Wave6(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
{
	// ノ芠代
	Enemy wave6MesaureEnemy;
	wave6MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	Bezier straightLine1({ POINTF{0,0},POINTF{0,150} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(60);
	Bezier curve1({ POINTF{0,0},POINTF{ -77,50},POINTF{ -154,-50},POINTF{ -231,0} });
	vector<POINTF> wave6 = straightLine1Speeds;
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	wave6.insert(wave6.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave6.insert(wave6.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	int frame = 1100;
	int wave6X = playerArea->GetLeft() + playerArea->GetWidth() - wave6MesaureEnemy.GetWidth() * 5 / 2;
	for (int i = 0; i < 6; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave6X, (float)-wave6MesaureEnemy.GetHeight() };
		mapData.speeds = wave6;
		(*mapDatum)[frame] = { mapData };

		mapData.location.x += 30;
		(*mapDatum)[frame].push_back(mapData);

		frame += 12;
		wave6X -= wave6MesaureEnemy.GetWidth() / 3;
	}
}

void MapCreator::initStage1Wave7(MovingObject* playerArea, map<size_t, vector<MapData>>* mapDatum)
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
	Enemy wave7MesaureEnemy;
	wave7MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));

	int frame = 1180;
	int wave7X = playerArea->GetLeft() + wave7MesaureEnemy.GetWidth() * 3 / 2;
	for (int i = 0; i < 8; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave7X, (float)-wave7MesaureEnemy.GetHeight() };
		mapData.speeds = wave1;
		(*mapDatum)[frame] = { mapData };

		mapData.location.x -= 30;
		(*mapDatum)[frame].push_back(mapData);

		frame += 12;
		wave7X += wave7MesaureEnemy.GetWidth() / 3;
	}
}

