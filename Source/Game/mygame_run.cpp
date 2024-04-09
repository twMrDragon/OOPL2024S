#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"


using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (mainStage == GAME_STAGE) {
		// player
		player.updateLocationFBySpeed();
		fixPlayerLocation();

		// player bullet
		for (size_t i = 0; i < playerBullets.size(); i++)
		{
			playerBullets[i].updateLocationFBySpeed();
		}
		if (fire) {
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite64.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(player.getLocationF().x + (player.GetWidth() - bullet.GetWidth()) / 2.0f, player.getLocationF().y + (player.GetHeight() - bullet.GetHeight()) / 2.0f);
			bullet.setSpeedY(-5);
			playerBullets.push_back(bullet);
		}
		checkBulletHitEnemy();

		// falling object
		for (size_t i = 0; i < fallingObjects.size(); i++)
		{
			fallingObjects[i].updateLocationFBySpeed();
			if (fallingObjects[i].IsOverlap(fallingObjects[i], player))
			{
				fallingObjects.erase(fallingObjects.begin() + i);
				i--;
				Power++;
			}
		}
		// generate enemy
		map<size_t, vector<MapData>>::iterator iter = mapDatum.find(frameCounter);
		if (iter != mapDatum.end()) {
			for (size_t i = 0; i < iter->second.size(); i++)
			{
				Enemy enemy;
				enemy.LoadBitmapByString(iter->second[i].resource, iter->second[i].colorFilter);
				enemy.setLocationF(iter->second[i].location.x, iter->second[i].location.y);
				enemy.setSpeeds(iter->second[i].speeds);
				enemy.setAction(iter->second[i].enemyAction);
				enemies.push_back(enemy);
			}
		}
		frameCounter += 1;
		// enemy
		for (size_t i = 0; i < enemies.size(); i++)
			enemies[i].update(player, &enemyBullets);
		// enemy bullets
		for (size_t i = 0; i < enemyBullets.size(); i++)
			enemyBullets[i].updateLocationFBySpeed();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	initMenu();
	initGame();
	GotoGameState(GAME_STATE_RUN);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (mainStage == MENU_STAGE) {
		if (nChar == VK_UP) {
			if (menuStage == MAIN_MENU)
				setMainMenuSelection(-1);
		}
		else if (nChar == VK_DOWN) {
			if (menuStage == MAIN_MENU)
				setMainMenuSelection(1);
		}
		// key z
		else if (nChar == 0x5A) {
			if (menuStage == MAIN_MENU)
				if (mainMenuButtonSelectIndex == START)
					mainStage = GAME_STAGE;
		}
	}
	else {
		if (nChar == VK_UP) {
			player.setSpeedY(player.getSpeedY() - playerDelta);
		}
		else if (nChar == VK_DOWN) {
			player.setSpeedY(player.getSpeedY() + playerDelta);
		}
		else if (nChar == VK_LEFT) {
			player.setSpeedX(player.getSpeedX() - playerDelta);
		}
		else if (nChar == VK_RIGHT) {
			player.setSpeedX(player.getSpeedX() + playerDelta);
		}
		else if (nChar == 0x5A) {
			fire = true;
		}
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (mainStage == GAME_STAGE) {
		if (nChar == VK_UP) {
			player.setSpeedY(player.getSpeedY() + playerDelta);
		}
		else if (nChar == VK_DOWN) {
			player.setSpeedY(player.getSpeedY() - playerDelta);
		}
		else if (nChar == VK_LEFT) {
			player.setSpeedX(player.getSpeedX() + playerDelta);
		}
		else if (nChar == VK_RIGHT) {
			player.setSpeedX(player.getSpeedX() - playerDelta);
		}
		else if (nChar == 0x5A) {
			fire = false;
		}
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (mainStage == MENU_STAGE) {
		background.ShowBitmap();
		showMainMenuButtons();
	}
	else {
		showGame();
	}
}

void CGameStateRun::showMainMenuButtons() {
	int d = 3;
	for (size_t i = 0; i < mainMenuButtons.size(); i++)
	{
		CMovingBitmap button = mainMenuButtons[i];
		if (button.GetFrameIndexOfBitmap() == 0 && mainMenuButtonSelectIndex == i) {
			button.SetTopLeft(button.GetLeft() - d, button.GetTop() - d);
			button.SetFrameIndexOfBitmap(1);
		}
		else if (button.GetFrameIndexOfBitmap() == 1 && mainMenuButtonSelectIndex != i) {
			button.SetTopLeft(button.GetLeft() + d, button.GetTop() + d);
			button.SetFrameIndexOfBitmap(0);
		}
		button.ShowBitmap();
	}
}

void CGameStateRun::initMenu() {
	// menu background
	background.LoadBitmapByString({ "Resources\\Image\\TL\\title00\\Sprite0.bmp" });
	background.SetTopLeft(0, 0);
	// main menu
	vector<vector<string>> buttonImagePaths = {
		{ "Resources\\Image\\TL\\title01\\Sprite10.bmp","Resources\\Image\\TL\\title01s\\Sprite10.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite11.bmp","Resources\\Image\\TL\\title01s\\Sprite11.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite26.bmp","Resources\\Image\\TL\\title01s\\Sprite26.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite12.bmp","Resources\\Image\\TL\\title01s\\Sprite12.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite13.bmp","Resources\\Image\\TL\\title01s\\Sprite13.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite25.bmp","Resources\\Image\\TL\\title01s\\Sprite25.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite15.bmp","Resources\\Image\\TL\\title01s\\Sprite15.bmp" },
		{ "Resources\\Image\\TL\\title01\\Sprite14.bmp","Resources\\Image\\TL\\title01s\\Sprite14.bmp" },
	};
	vector<vector<int>> buttonLocations = {
		{447,199},
		{438, 227},
		{428, 256},
		{418, 284},
		{408, 312},
		{398, 340},
		{388, 369},
		{378, 396}
	};
	for (size_t i = 0; i < buttonImagePaths.size(); i++)
	{
		CMovingBitmap button;
		button.LoadBitmapByString(buttonImagePaths[i], RGB(0, 0, 0));
		button.SetTopLeft(buttonLocations[i][0], buttonLocations[i][1]);
		mainMenuButtons.push_back(button);
	}
}

void CGameStateRun::setMainMenuSelection(int direction) {
	mainMenuButtonSelectIndex += direction;
	if (mainMenuButtonSelectIndex < 0)
		mainMenuButtonSelectIndex = 0;
	else if (mainMenuButtonSelectIndex == mainMenuButtons.size())
		mainMenuButtonSelectIndex = mainMenuButtons.size() - 1;
}

void CGameStateRun::initGame() {
	// player
	player.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite0.bmp" }, RGB(205, 205, 205));
	player.setLocationF(200, 400);
	// player moveing area
	playerArea.LoadEmptyBitmap(448, 384);
	playerArea.SetTopLeft(32, 16);
	// interface background
	for (int filename : {5, 6, 7, 23}) {
		CMovingBitmap interfaceBackgound;
		interfaceBackgound.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite" + to_string(filename) + ".bmp" });
		interfaceBackgroundResource.push_back(interfaceBackgound);
	}
	// live and bomb star
	RedStar.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite17.bmp" }, RGB(0, 0, 0));
	GreenStar.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite18.bmp" }, RGB(0, 0, 0));
	// interface labels
	vector<vector<string>> labelImagePaths = {
		{ "Resources\\Image\\CM\\front\\Sprite9.bmp" },
		{ "Resources\\Image\\CM\\front\\Sprite8.bmp" },
		{ "Resources\\Image\\CM\\front\\Sprite10.bmp" },
		{ "Resources\\Image\\CM\\front\\Sprite11.bmp" },
		{ "Resources\\Image\\CM\\front\\Sprite15.bmp" },
		{ "Resources\\Image\\CM\\front\\Sprite16.bmp" },
		{ "Resources\\Image\\CM\\front\\Sprite20.bmp" },
	};
	vector<vector<int>> labelLocations = {
		{432, 58},
		{431, 82},
		{432, 121},
		{432, 146},
		{432, 186},
		{431, 206},
		{432, 226}
	};
	for (size_t i = 0; i < labelImagePaths.size(); i++)
	{
		CMovingBitmap label;
		label.LoadBitmapByString(labelImagePaths[i], RGB(0, 0, 0));
		label.SetTopLeft(labelLocations[i][0], labelLocations[i][1]);
		gameInterface.push_back(label);
	}
	// number system
	for (int i = 0; i < 5; i++) {
		NumberSystem numberSystem;
		numberSystems.push_back(numberSystem);
	}
	numberSystems[0].setMinDigit(9);
	numberSystems[0].setXY(496, 58);
	numberSystems[1].setMinDigit(9);
	numberSystems[1].setXY(496, 82);
	numberSystems[2].setXY(496, 186);
	numberSystems[3].setXY(496, 206);
	numberSystems[4].setXY(496, 226);

	initMapDatum();
}

void CGameStateRun::initMapDatum() {
	// stage 1
	// wave 1
	Bezier straightLine1({ POINTF{0,0},POINTF{0,150} });
	vector<POINTF> straightLine1Speeds = straightLine1.getEachSpeed(60);
	vector<POINTF> wave1 = straightLine1Speeds;
	Bezier curve1({ POINTF{0,0},POINTF{77,50},POINTF{154,-50},POINTF{231,0} });
	vector<POINTF> curve1Speeds = curve1.getEachSpeed(90);
	wave1.insert(wave1.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
	wave1.insert(wave1.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	Enemy wave1MesaureEnemy;
	wave1MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));
	int frame = 0;
	int wave1X = playerArea.GetLeft() + wave1MesaureEnemy.GetWidth() * 3 / 2;
	for (int i = 0; i < 5; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave1X, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave1;
		mapDatum[frame] = { mapData };
		frame += 12;
		wave1X += wave1MesaureEnemy.GetWidth() / 3;
	}

	// wave 2
	Bezier curve2({ POINTF{0,0},POINTF{ -77,50},POINTF{ -154,-50},POINTF{ -231,0} });
	vector<POINTF> wave2 = straightLine1Speeds;
	vector<POINTF> curve2Speeds = curve2.getEachSpeed(90);
	wave2.insert(wave2.end(), curve2Speeds.begin() + 1, curve2Speeds.end());
	wave2.insert(wave2.end(), straightLine1Speeds.begin() + 1, straightLine1Speeds.end());

	frame = 100;
	int wave2X = playerArea.GetLeft() + playerArea.GetWidth() - wave1MesaureEnemy.GetWidth() * 5 / 2;
	for (int i = 0; i < 8; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave2X, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave2;
		mapDatum[frame] = { mapData };
		frame += 12;
		wave2X -= wave1MesaureEnemy.GetWidth() / 3;
	}

	// wave 3
	Bezier straightLine3({ POINTF{0,0},POINTF{0,220} });
	vector<POINTF> straightLine3Speeds = straightLine3.getEachSpeed(75);
	vector<POINTF> wave31 = straightLine3Speeds;
	vector<POINTF> wave32 = straightLine3Speeds;
	Bezier curve31({ POINTF{0,0},POINTF{ -100,150},POINTF{ -200,30} });
	vector<POINTF> curve31Speeds = curve31.getEachSpeed(90);
	Bezier curve32({ POINTF{0,0},POINTF{100,150},POINTF{200,30} });
	vector<POINTF> curve32Speeds = curve32.getEachSpeed(90);
	wave31.insert(wave31.end(), curve31Speeds.begin() + 1, curve31Speeds.end());
	wave32.insert(wave32.end(), curve32Speeds.begin() + 1, curve32Speeds.end());

	frame = 250;
	int wave3X1 = playerArea.GetLeft() + wave1MesaureEnemy.GetWidth();
	int wave3X2 = playerArea.GetLeft() + playerArea.GetWidth() - wave1MesaureEnemy.GetWidth() * 2;
	for (int i = 0; i < 10; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave3X1, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave31;
		mapDatum[frame] = { mapData };

		mapData.location = POINTF{ (float)wave3X2, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave32;
		mapDatum[frame].push_back(mapData);

		frame += 12;
		wave3X1 += (wave1MesaureEnemy.GetWidth() / 2 - 1);
		wave3X2 -= (wave1MesaureEnemy.GetWidth() / 2 - 1);
	}

	// wave 4
	frame = 400;
	Enemy wave4MesaureEnemy;
	wave4MesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite8.bmp" }, RGB(254, 254, 254));
	Bezier straightLine41({ POINTF{0,0} ,POINTF{0,130} });
	Bezier straightLine42({ POINTF{0,0 }, POINTF{ 0,-130 } });
	Bezier curve41({ POINTF{0,0},POINTF{ -25,60},POINTF{ -50,0} });
	Bezier curve42({ POINTF{0,0},POINTF{25,60},POINTF{50,0} });
	Bezier wait({ POINTF{0,0},POINTF{0,0 } });
	vector<POINTF> straightLine41Speeds = straightLine41.getEachSpeed(40);
	vector<POINTF> straightLine42Speeds = straightLine42.getEachSpeed(40);
	vector<POINTF> curve41Speeds = curve41.getEachSpeed(30);
	vector<POINTF> curve42Speeds = curve42.getEachSpeed(30);
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
		POINTF{(float)playerArea.GetLeft() + 30,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 150,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 120,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 58,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 16,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 75,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 180,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 60,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 28,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 195,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 15,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 105,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 135,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 70,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + 30,(float)-wave4MesaureEnemy.GetHeight()},
		POINTF{(float)playerArea.GetLeft() + playerArea.GetWidth() - 195,(float)-wave4MesaureEnemy.GetHeight()},
	};
	vector<size_t> wave4DeltaFrame = { 45,39,39,39,34,34,29,29,29,24,24,24,24,24,19,0 };


	for (size_t i = 0; i < wave4Points.size(); i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite8.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = wave4Points[i];

		mapData.enemyAction[40] = { &BulletCreator::createStage1PinkEnemyBullet };

		if (wave4Points[i].x + wave4MesaureEnemy.GetWidth() / 2 > playerArea.GetTop() + playerArea.GetWidth() / 2) {
			mapData.speeds = wave4Right;
		}
		else {
			mapData.speeds = wave4Left;
		}
		mapDatum[frame] = { mapData };
		frame += wave4DeltaFrame[i];
	}

	// wave 5
	frame = 900;
	vector<POINTF> wave5Points = {
		POINTF{210,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{290,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{217,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{357,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{160,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{67,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{270,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{100,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{277,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{297,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{177,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{172,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{179,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{62,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{255,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{262,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{152,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{325,(float)-wave1MesaureEnemy.GetHeight()},
		POINTF{180,(float)-wave1MesaureEnemy.GetHeight()},
	};
	vector<int> wave5MovingHeight = {
		102,102,240,99,240,99,99,240,240,93,99,99,99,240,99,99,99,240,240
	};
	vector<bool> wave5TurnDirection = {
		false,true,true,true,true,true,false,false,true,true,true,false,true,true,false,false,true,true,false
	};
	Bezier curve5Right({ POINTF{0,-40},POINTF{0,5},POINTF{-5,0},POINTF{40,0} });
	vector<POINTF> curve5RightSpeeds = curve5Right.getEachSpeed(30);
	curve5RightSpeeds[curve5RightSpeeds.size() - 1].y = 0;
	Bezier curve5Left({ POINTF{0,-40},POINTF{0,5},POINTF{5,0},POINTF{ -40,0} });
	vector<POINTF> curve5LeftSpeeds = curve5Left.getEachSpeed(30);
	curve5LeftSpeeds[curve5LeftSpeeds.size() - 1].y = 0;
	for (size_t i = 0; i < wave5Points.size(); i++)
	{
		vector<POINTF> speeds = {};
		for (int j = 0; j < wave5MovingHeight[i] / 3; j++)
			speeds.push_back(POINTF{ 0, 3 });
		if (wave5TurnDirection[i])
		{
			speeds.insert(speeds.end(), curve5RightSpeeds.begin() + 1, curve5RightSpeeds.end());
		}
		else {
			speeds.insert(speeds.end(), curve5LeftSpeeds.begin() + 1, curve5LeftSpeeds.end());
		}


		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = wave5Points[i];
		mapData.speeds = speeds;
		mapDatum[frame] = { mapData };
		frame += 6;
	}

	// wave 6
	frame = 1100;
	int wave6X = playerArea.GetLeft() + playerArea.GetWidth() - wave1MesaureEnemy.GetWidth() * 5 / 2;
	for (int i = 0; i < 6; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave6X, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave2;
		mapDatum[frame] = { mapData };

		mapData.location.x += 30;
		mapDatum[frame].push_back(mapData);

		frame += 12;
		wave6X -= wave1MesaureEnemy.GetWidth() / 3;
	}
	// wave 7
	frame = 1180;
	int wave7X = playerArea.GetLeft() + wave1MesaureEnemy.GetWidth() * 3 / 2;
	for (int i = 0; i < 8; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = POINTF{ (float)wave7X, (float)-wave1MesaureEnemy.GetHeight() };
		mapData.speeds = wave1;
		mapDatum[frame] = { mapData };

		mapData.location.x -= 30;
		mapDatum[frame].push_back(mapData);

		frame += 12;
		wave7X += wave1MesaureEnemy.GetWidth() / 3;
	}
}

void CGameStateRun::showGame() {
	// player
	player.ShowBitmap();
	// player bullets
	for (size_t i = 0; i < playerBullets.size(); i++)
		playerBullets[i].ShowBitmap();
	// falling object
	for (size_t i = 0; i < fallingObjects.size(); i++)
		fallingObjects[i].ShowBitmap();
	// enemy
	for (size_t i = 0; i < enemies.size(); i++)
		enemies[i].ShowBitmap();
	// enemy bullets
	for (size_t i = 0; i < enemyBullets.size(); i++)
		enemyBullets[i].ShowBitmap();


	// interface
	// interface border
	showBorder();
	// interfaece labe
	for (size_t i = 0; i < gameInterface.size(); i++)
		gameInterface[i].ShowBitmap();
	// number system
	numberSystems[0].showNumber(1000000);
	numberSystems[1].showNumber(0);
	numberSystems[2].showNumber(Power);
	numberSystems[3].showNumber(0);
	numberSystems[4].showNumber(0);
	// player star
	for (int i = 0; i < RemainingLives; i++)
	{
		RedStar.SetTopLeft(496 + i * RedStar.GetWidth(), 122);
		RedStar.ShowBitmap();
	}
	// bomb star
	for (int i = 0; i < Bomb; i++)
	{
		GreenStar.SetTopLeft(496 + i * GreenStar.GetWidth(), 146);
		GreenStar.ShowBitmap();
	}
}

void CGameStateRun::showBorder() {
	// right border
	CMovingBitmap leftBackground = interfaceBackgroundResource[0];
	for (int y = 0; y < 480; y += leftBackground.GetHeight())
	{
		leftBackground.SetTopLeft(0, y);
		leftBackground.ShowBitmap();
	}
	// top, bottom border
	CMovingBitmap topBackground = interfaceBackgroundResource[1];
	CMovingBitmap bottomBackground = interfaceBackgroundResource[2];
	for (int x = topBackground.GetWidth(); x < playerArea.GetLeft() + playerArea.GetWidth(); x += topBackground.GetWidth())
	{
		topBackground.SetTopLeft(x, 0);
		topBackground.ShowBitmap();
		bottomBackground.SetTopLeft(x, 480 - bottomBackground.GetHeight());
		bottomBackground.ShowBitmap();
	}
	// right border
	CMovingBitmap rightBackground = interfaceBackgroundResource[3];
	for (int y = 0; y < 480; y += rightBackground.GetHeight())
	{
		for (int x = playerArea.GetLeft() + playerArea.GetWidth(); x < 640; x += rightBackground.GetWidth())
		{
			rightBackground.SetTopLeft(x, y);
			rightBackground.ShowBitmap();
		}
	}
}

void CGameStateRun::fixPlayerLocation() {
	// hit top bound
	if (player.getLocationF().y < playerArea.GetTop()) {
		player.setLocationF(player.getLocationF().x, (float)playerArea.GetTop());
	}
	// hit left bound
	if (player.getLocationF().x < playerArea.GetLeft())
	{
		player.setLocationF((float)playerArea.GetLeft(), player.getLocationF().y);
	}
	// hit bottom bound
	if (player.getLocationF().y + player.GetHeight() > playerArea.GetTop() + playerArea.GetHeight()) {
		player.setLocationF(player.getLocationF().x, (float)(playerArea.GetTop() + playerArea.GetHeight() - player.GetHeight()));
	}
	// hit right bound
	if (player.getLocationF().x + player.GetWidth() > playerArea.GetLeft() + playerArea.GetWidth())
	{
		player.setLocationF((float)(playerArea.GetLeft() + playerArea.GetWidth() - player.GetWidth()), player.getLocationF().y);
	}
}

void CGameStateRun::checkBulletHitEnemy() {
	for (size_t i = 0; i < playerBullets.size(); i++) {
		for (size_t j = 0; j < enemies.size(); j++) {
			if (playerBullets[i].IsOverlap(playerBullets[i], enemies[j])) {
				addFallingObject(enemies[j]);
				playerBullets.erase(playerBullets.begin() + i);
				enemies.erase(enemies.begin() + j);
				break;
			}
		}
	}
}

void CGameStateRun::addFallingObject(MovingObject enemy) {
	MovingObject falling;
	falling.LoadBitmapByString({ "Resources\\Image\\CM\\etama3\\Sprite0.bmp" }, RGB(65, 52, 52));
	float left = enemy.getLocationF().x + (enemy.GetWidth() - falling.GetWidth()) / 2.0f;
	float top = enemy.getLocationF().y + (enemy.GetHeight() - falling.GetHeight()) / 2.0f;
	falling.setLocationF(left, top);
	falling.setSpeed(POINTF{ 0, 3 });
	fallingObjects.push_back(falling);
}
