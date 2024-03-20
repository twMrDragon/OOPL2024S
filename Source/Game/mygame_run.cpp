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
	initMenuButtons();
	initGame();
	GotoGameState(GAME_STATE_RUN);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (mainStage == MENU_STAGE) {
		if (nChar == VK_UP) {
			if (mainStage == MENU_STAGE)
				updateSelectIndex(-1);
		}
		else if (nChar == VK_DOWN) {
			if (mainStage == MENU_STAGE)
				updateSelectIndex(1);
		}
		else if (nChar == 0x5A) {
			if (mainStage == MENU_STAGE) {
				if (buttonSelectIndex == 0)
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
		showMenuButtons();
	}
	else {
		showGame();
	}
}

void CGameStateRun::initBackground() {
	background.LoadBitmapByString({ "Resources\\Image\\TL\\title00\\Sprite0.bmp" });
	background.SetTopLeft(0, 0);
}

void CGameStateRun::showMenuButtons() {
	int d = 5;
	for (size_t i = 0; i < menuButtons.size(); i++)
	{
		CMovingBitmap button = menuButtons[i];
		if (button.GetFrameIndexOfBitmap() == 0 && buttonSelectIndex == i) {
			button.SetTopLeft(button.GetLeft() - d, button.GetTop() - d);
			button.SetFrameIndexOfBitmap(1);
		}
		else if (button.GetFrameIndexOfBitmap() == 1 && buttonSelectIndex != i) {
			button.SetTopLeft(button.GetLeft() + d, button.GetTop() + d);
			button.SetFrameIndexOfBitmap(0);
		}
		button.ShowBitmap();
	}
}

void CGameStateRun::initMenuButtons() {
	int startX = 448;
	int startY = 200;
	int dx = -10;
	int dy = 28;
	vector<vector<string>> imagePath = {
		{"Resources\\Image\\TL\\title01\\Sprite10.bmp","Resources\\Image\\TL\\title01s\\Sprite10.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite11.bmp","Resources\\Image\\TL\\title01s\\Sprite11.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite26.bmp","Resources\\Image\\TL\\title01s\\Sprite26.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite12.bmp","Resources\\Image\\TL\\title01s\\Sprite12.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite13.bmp","Resources\\Image\\TL\\title01s\\Sprite13.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite25.bmp","Resources\\Image\\TL\\title01s\\Sprite25.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite15.bmp","Resources\\Image\\TL\\title01s\\Sprite15.bmp"},
		{"Resources\\Image\\TL\\title01\\Sprite14.bmp","Resources\\Image\\TL\\title01s\\Sprite14.bmp"}
	};
	for (size_t i = 0; i < menuButtons.size(); i++)
	{
		menuButtons[i].LoadBitmapByString(imagePath[i], RGB(0, 0, 0));
		menuButtons[i].SetTopLeft(startX + dx * i, startY + dy * i);
	}
}

void CGameStateRun::updateSelectIndex(int direction) {
	buttonSelectIndex += direction;
	if (buttonSelectIndex < 0)
		buttonSelectIndex = 0;
	else if (buttonSelectIndex == menuButtons.size())
		buttonSelectIndex = menuButtons.size() - 1;
}

void CGameStateRun::initGame() {
	player.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite0.bmp" }, RGB(205, 205, 205));
	player.SetTopLeft(200, 400);
}

void CGameStateRun::showGame() {
	player.ShowBitmap();
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		playerBullets[i].ShowBitmap();
	}
}