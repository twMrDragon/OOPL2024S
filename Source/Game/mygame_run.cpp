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
	player.updateTopLeftBySpeed();
	fixPlayerLocation();

	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		playerBullets[i].updateTopLeftBySpeed();
	}
	if (fire) {
		MovingObject bullet;
		bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite64.bmp" }, RGB(255, 255, 255));
		bullet.SetTopLeft(player.GetLeft(), player.GetTop() + bullet.GetHeight());
		bullet.setSpeedY(-5);
		playerBullets.push_back(bullet);
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	initBackground();
	initMenu();
	initGame();
	GotoGameState(GAME_STATE_RUN);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (mainStage == MENU_STAGE) {
		if (nChar == VK_UP) {
			if (mainStage == MENU_STAGE)
				setMainMenuSelection(-1);
		}
		else if (nChar == VK_DOWN) {
			if (mainStage == MENU_STAGE)
				setMainMenuSelection(1);
		}
		else if (nChar == 0x5A) {
			if (mainStage == MENU_STAGE) {
				if (mainMenuSelectIndex == 0)
					mainStage = GAME_STAGE;
			}
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

void CGameStateRun::initBackground() {
	background.LoadBitmapByString({ "Resources\\Image\\TL\\title00\\Sprite0.bmp" });
	background.SetTopLeft(0, 0);
}

void CGameStateRun::showMainMenuButtons() {
	int d = 3;
	for (size_t i = 0; i < mainMenuButtons.size(); i++)
	{
		CMovingBitmap button = mainMenuButtons[i];
		if (button.GetFrameIndexOfBitmap() == 0 && mainMenuSelectIndex == i) {
			button.SetTopLeft(button.GetLeft() - d, button.GetTop() - d);
			button.SetFrameIndexOfBitmap(1);
		}
		else if (button.GetFrameIndexOfBitmap() == 1 && mainMenuSelectIndex != i) {
			button.SetTopLeft(button.GetLeft() + d, button.GetTop() + d);
			button.SetFrameIndexOfBitmap(0);
		}
		button.ShowBitmap();
	}
}

void CGameStateRun::initMenu() {
	// main menu
	CMovingBitmap startButton;
	startButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite10.bmp","Resources\\Image\\TL\\title01s\\Sprite10.bmp" });
	startButton.SetTopLeft(447, 199);
	mainMenuButtons.push_back(startButton);

	CMovingBitmap extraStartButton;
	extraStartButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite11.bmp","Resources\\Image\\TL\\title01s\\Sprite11.bmp" });
	extraStartButton.SetTopLeft(438, 227);
	mainMenuButtons.push_back(extraStartButton);

	CMovingBitmap practiceStartButton;
	practiceStartButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite26.bmp","Resources\\Image\\TL\\title01s\\Sprite26.bmp" });
	practiceStartButton.SetTopLeft(428, 256);
	mainMenuButtons.push_back(practiceStartButton);

	CMovingBitmap replayButton;
	replayButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite12.bmp","Resources\\Image\\TL\\title01s\\Sprite12.bmp" });
	replayButton.SetTopLeft(418, 284);
	mainMenuButtons.push_back(replayButton);


	CMovingBitmap scoreButton;
	scoreButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite13.bmp","Resources\\Image\\TL\\title01s\\Sprite13.bmp" });
	scoreButton.SetTopLeft(408, 312);
	mainMenuButtons.push_back(scoreButton);


	CMovingBitmap musicRoomButton;
	musicRoomButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite25.bmp","Resources\\Image\\TL\\title01s\\Sprite25.bmp" });
	musicRoomButton.SetTopLeft(398, 340);
	mainMenuButtons.push_back(musicRoomButton);


	CMovingBitmap optionButton;
	optionButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite15.bmp","Resources\\Image\\TL\\title01s\\Sprite15.bmp" });
	optionButton.SetTopLeft(388, 369);
	mainMenuButtons.push_back(optionButton);


	CMovingBitmap quitButton;
	quitButton.LoadBitmapByString({ "Resources\\Image\\TL\\title01\\Sprite14.bmp","Resources\\Image\\TL\\title01s\\Sprite14.bmp" });
	quitButton.SetTopLeft(378, 396);
	mainMenuButtons.push_back(quitButton);
}

void CGameStateRun::setMainMenuSelection(int direction) {
	mainMenuSelectIndex += direction;
	if (mainMenuSelectIndex < 0)
		mainMenuSelectIndex = 0;
	else if (mainMenuSelectIndex == mainMenuButtons.size())
		mainMenuSelectIndex = mainMenuButtons.size() - 1;
}

void CGameStateRun::initGame() {
	// player
	player.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite0.bmp" }, RGB(205, 205, 205));
	player.SetTopLeft(200, 400);
	// player moveing area
	playerArea.LoadEmptyBitmap(447, 383);
	playerArea.SetTopLeft(32, 16);

	// interface labels
	CMovingBitmap maxScoreLabel;
	maxScoreLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite9.bmp" }, RGB(0, 0, 0));
	maxScoreLabel.SetTopLeft(432, 58);
	gameInterface.push_back(maxScoreLabel);

	CMovingBitmap scoreLabel;
	scoreLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite8.bmp" }, RGB(0, 0, 0));
	scoreLabel.SetTopLeft(431, 82);
	gameInterface.push_back(scoreLabel);

	CMovingBitmap playerLabel;
	playerLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite10.bmp" }, RGB(0, 0, 0));
	playerLabel.SetTopLeft(432, 121);
	gameInterface.push_back(playerLabel);

	CMovingBitmap bombLabel;
	bombLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite11.bmp" }, RGB(0, 0, 0));
	bombLabel.SetTopLeft(432, 146);
	gameInterface.push_back(bombLabel);

	CMovingBitmap powerLabel;
	powerLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite15.bmp" }, RGB(0, 0, 0));
	powerLabel.SetTopLeft(432, 186);
	gameInterface.push_back(powerLabel);

	CMovingBitmap grazeLabel;
	grazeLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite16.bmp" }, RGB(0, 0, 0));
	grazeLabel.SetTopLeft(431, 206);
	gameInterface.push_back(grazeLabel);

	CMovingBitmap pointLabel;
	pointLabel.LoadBitmapByString({ "Resources\\Image\\CM\\front\\Sprite20.bmp" }, RGB(0, 0, 0));
	pointLabel.SetTopLeft(432, 226);
	gameInterface.push_back(pointLabel);
}

void CGameStateRun::showGame() {
	player.ShowBitmap();
	for (size_t i = 0; i < gameInterface.size(); i++)
		gameInterface[i].ShowBitmap();
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		playerBullets[i].ShowBitmap();
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