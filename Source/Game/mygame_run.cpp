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
		player.reduceInvincible();
		// player
		for (size_t i = 0; i < enemyBullets.size(); i++)
		{
			if (player.isDeath(enemyBullets[i]))
			{

				player.setInvincible(120);
				player.setPower(0);
				player.setRemainingLives(player.getRemainingLives() - 1);
				player.setRangeAnimation(0, 3, 100, false);//not enough
				
			}
			if (player.getInvincible() == 1) {
				player.setRangeAnimation(1, 3, 10, false);
			}
		}
		player.updateLocationFBySpeed();
		fixPlayerLocation();


		// generate player bullet, move bullet and erase
		updatePlayerBullet();
		checkBulletHitEnemy();

		// falling object
		for (size_t i = 0; i < fallingObjects.size(); i++)
		{
			fallingObjects[i].updateLocationFBySpeed();
			if (fallingObjects[i].IsOverlap(fallingObjects[i], player))
			{
				fallingObjects.erase(fallingObjects.begin() + i);
				i--;
				player.setPower(player.getPower() + 1);
			}
		}
		// generate enemy, move enemy and erase enemy leave player area
		// same of enemy bullet
		updateEnemy();

		// boss
		std::shared_ptr<Boss> bossCreated = MapCreator::getCurrentBoss(frameCounter, playerArea);
		if (bossCreated != nullptr)
		{
			this->boss = bossCreated;
		}
		if (this->boss != nullptr)
		{
			this->boss->update(player, &enemyBullets);
			if (this->boss->onLeave(playerArea))
			{
				this->boss = nullptr;
			}
		}
		frameCounter += 1;
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
;
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
			//4-10 513
			//player.setRangeAnimation(4, 10, 100, true);
			//player.ToggleAnimation();
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
			//player.setRangeAnimation(1, 3, 100, true);
			//player.startToggleAnimation();
		}
		else if (nChar == VK_RIGHT) {
			player.setSpeedX(player.getSpeedX() - playerDelta);
			/*
			*/
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
	//player.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite0.bmp" }, RGB(205, 205, 205));
	player.onInit();
	player.setLocationF(200, 400);
	// player moveing area
	playerArea.LoadEmptyBitmap(448, 384);
	playerArea.setLocationF(32.0f, 16.0f);

	player.setRangeAnimation(1, 3, 150, false);
	player.startToggleAnimation();
	// interface background
	for (const int filename : {5, 6, 7, 23}) {
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
	// show score and player data
	for (int i = 0; i < 5; i++) {
		NumberSystem numberSystem;
		numberSystem.onInit();
		numberSystems.push_back(numberSystem);
	}
	numberSystems[0].setMinDigit(9);
	numberSystems[0].setXY(496, 58);
	numberSystems[1].setMinDigit(9);
	numberSystems[1].setXY(496, 82);
	numberSystems[2].setXY(496, 186);
	numberSystems[3].setXY(496, 206);
	numberSystems[4].setXY(496, 226);

	// boss timer
	bossTimer.onInit();
	bossTimer.setMinDigit(2);
	bossTimer.setXY(playerArea.GetLeft() + playerArea.GetWidth() - 32, playerArea.GetTop());

	MapCreator::onInit(&playerArea, &mapDatum);
}

void CGameStateRun::showGame() {
	// player
	//player.SetAnimation(1, false);
	player.handMadeShow();
	
	//player.ShowBitmap();
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
	// boss
	if (this->boss != nullptr) {
		boss->show();
		bossTimer.showNumber(boss->getTimer() / 30);
	}


	// interface
	// interface border
	showBorder();
	// interfaece labe
	for (size_t i = 0; i < gameInterface.size(); i++)
		gameInterface[i].ShowBitmap();
	// number system
	numberSystems[0].showNumber(1000000);
	numberSystems[1].showNumber(0);
	numberSystems[2].showNumber(player.getPower());
	numberSystems[3].showNumber(0);
	numberSystems[4].showNumber(0);
	// player star
	for (int i = 0; i < player.getRemainingLives(); i++)
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

void CGameStateRun::updateEnemy()
{
	// generate emeny
	map<size_t, vector<MapData>>::iterator iter = mapDatum.find(frameCounter);
	if (iter != mapDatum.end()) {
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			Enemy enemy;
			enemy.LoadBitmapByString(iter->second[i].resource, iter->second[i].colorFilter);
			enemy.setLocationF(iter->second[i].location.x, iter->second[i].location.y);
			if (iter->second[i].aimTarget == MapData::AIM_TARGET::NO) {
				enemy.setSpeeds(iter->second[i].speeds);
			}
			else {
				double angle2Player = enemy.angle2Target(player);
				float speed = 3;
				float x = (float)cos(angle2Player * M_PI / 180) * speed;
				float y = (float)sin(angle2Player * M_PI / 180) * speed;
				enemy.setSpeed(POINTF{ x,y });
			}

			enemy.setAction(iter->second[i].enemyAction);
			enemies.push_back(enemy);
		}
	}

	// erase enemy and move enemy
	for (size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i].onLeave(playerArea)) {
			enemies.erase(enemies.begin() + i);
			i--;
			continue;
		}
		else {
			enemies[i].update(&player, &enemyBullets);
		}
	}

	// enemy bullets
	for (size_t i = 0; i < enemyBullets.size(); i++) {
		if (!enemyBullets[i].IsOverlap(enemyBullets[i], playerArea))
		{
			enemyBullets.erase(enemyBullets.begin() + i);
			i--;
			continue;
		}
		else {
			enemyBullets[i].updateLocationFBySpeed();
		}
	}
}

void CGameStateRun::updatePlayerBullet()
{
	// erase bullet and move bullet
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		if (!playerBullets[i].IsOverlap(playerBullets[i], playerArea))
		{
			playerBullets.erase(playerBullets.begin() + i);
			i--;
			continue;
		}
		else {
			playerBullets[i].updateLocationFBySpeed();
		}
	}

	// generate
	if (fire) {
		//player.setPower(Power);
		vector<MovingObject> ms = player.attack();
		playerBullets.insert(playerBullets.end(), ms.begin(), ms.end());//wave1.insert(wave1.end(), curve1Speeds.begin() + 1, curve1Speeds.end());
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
