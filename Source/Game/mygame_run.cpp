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
{	// player
	player.updateTopLeftBySpeed();
	fixPlayerLocation();

	// bullet
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		playerBullets[i].updateTopLeftBySpeed();
	}
	if (fire) {
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite64.bmp" }, RGB(205, 205, 205));
		bullet.SetTopLeft(player.GetLeft(), player.GetTop() + bullet.GetHeight());
		bullet.setSpeedY(-5);
		playerBullets.push_back(bullet);
	}
	checkBulletHitEnemy();

	// falling object
	for (size_t i = 0; i < fallingObjects.size(); i++)
	{
		fallingObjects[i].updateTopLeftBySpeed();
		if (fallingObjects[i].IsOverlap(fallingObjects[i], player))
		{
			fallingObjects.erase(fallingObjects.begin() + i);
			Power++;
		}

	}
	if (mainStage == GAME_STAGE) {
		map<size_t, MapData>::iterator iter = mapDatum.find(frameCounter);
		if (iter != mapDatum.end()) {
			Enemy enemy;
			enemy.LoadBitmapByString(iter->second.resource, iter->second.colorFilter);
			enemy.SetTopLeft(iter->second.location.x, iter->second.location.y);
			enemy.setSpeeds(iter->second.speeds);
			enemies.push_back(enemy);
		}
		frameCounter += 1;
		for (size_t i = 0; i < enemies.size(); i++)
			enemies[i].updateBySpeeds();
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
	player.SetTopLeft(200, 400);
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
	int frame = 0;
	// test enemy
	Bezier straightLine({ Point(0,0),Point(0,150) });
	vector<Point> speedTemp = straightLine.getEachSpeed(60);
	vector<Point> wave1 = speedTemp;
	Bezier curve({ Point(0,0),Point(50,80),Point(190,-80),Point(240,0) });
	vector<Point> speedTemp2 = curve.getEachSpeed(90);
	wave1.insert(wave1.end(), speedTemp2.begin() + 1, speedTemp2.end());
	wave1.insert(wave1.end(), speedTemp.begin() + 1, speedTemp.end());

	int x = 80;
	Enemy mesaureEnemy;
	mesaureEnemy.LoadBitmapByString({ "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" }, RGB(254, 254, 254));
	for (size_t i = 0; i < 5; i++)
	{
		MapData mapData;
		mapData.resource = { "Resources\\Image\\ST\\stg1enm\\Sprite0.bmp" };
		mapData.colorFilter = RGB(254, 254, 254);
		mapData.location = Point(x, -mesaureEnemy.GetHeight());
		mapData.speeds = wave1;
		mapDatum[frame] = mapData;
		frame += 12;
		x += mesaureEnemy.GetWidth() / 3;
	}

	Bezier curve2({ Point(0,0),Point(50,80),Point(250,-80),Point(300,0) });

}

void CGameStateRun::showGame() {
	// player
	player.ShowBitmap();
	// bullet
	for (size_t i = 0; i < playerBullets.size(); i++)
		playerBullets[i].ShowBitmap();
	// enemy
	for (size_t i = 0; i < enemies.size(); i++)
		enemies[i].ShowBitmap();
	// falling object
	for (size_t i = 0; i < fallingObjects.size(); i++)
		fallingObjects[i].ShowBitmap();

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
	if (player.GetTop() < playerArea.GetTop()) {
		player.SetTopLeft(player.GetLeft(), playerArea.GetTop());
	}
	if (player.GetLeft() < playerArea.GetLeft())
	{
		player.SetTopLeft(playerArea.GetLeft(), player.GetTop());
	}
	if (player.GetTop() + player.GetHeight() > playerArea.GetTop() + playerArea.GetHeight()) {
		player.SetTopLeft(player.GetLeft(), playerArea.GetTop() + playerArea.GetHeight() - player.GetHeight());
	}
	if (player.GetLeft() + player.GetWidth() > playerArea.GetLeft() + playerArea.GetWidth())
	{
		player.SetTopLeft(playerArea.GetLeft() + playerArea.GetWidth() - player.GetWidth(), player.GetTop());
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
	int left = enemy.GetLeft() + (enemy.GetWidth() - falling.GetWidth()) / 2;
	int top = enemy.GetTop() + (enemy.GetHeight() - falling.GetHeight()) / 2;
	falling.SetTopLeft(left, top);
	falling.setSpeed(Point(0, 3));
	fallingObjects.push_back(falling);
}
