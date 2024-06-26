/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "MovingObject.h"
#include "NumberDisplay.h"
#include "Bezier.h"
#include "Enemy.h"
#include "MapCreator.h"
#include "MapData.h"
#include "BulletCreator.h"
#include "Player.h"
#include "ReimuB.h"
#include "Boss.h"
#include "EnemyBullet.h"
#include <memory>
#include "../Library/audio.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	enum MainStage {
		MENU_STAGE,
		GAME_STAGE
	};

	enum MenuStage {
		MAIN_MENU,
		LEVEL_SELECT,
		CHARCATER_SELECT,
		SKILL_SELECT
	};

	enum MainMenuButton {
		START,
		EXTRA_START,
		PRACTICE_START,
		REPLAY,
		SCORE,
		MUSIC_ROOM,
		OPTION,
		QUIT
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame* g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		//CMovingBitmap logo;								// csie的logo
		CMovingBitmap background;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		
		bool isMusicNow = false;
		CAudio* MenuMusic = CAudio::Instance();
		
		CMovingBitmap background;

		MainStage mainStage = MENU_STAGE;
		MenuStage menuStage = MAIN_MENU;
		bool isPause = false;
		/// 主選單
		vector<CMovingBitmap> mainMenuButtons;
		int mainMenuButtonSelectIndex = 0;
		void initMenu();
		void setMainMenuSelection(int direction);
		void showMainMenuButtons();

		void setPauseButtionSelection(int direction);
		void showPauseButtion();
		void setDeadButtionSelection(int direction);
		void showDeadButtion();
		void resetGame();

		int bounsPoint = 0;
		int showFrame = 0;
		bool isEnd = false;
		void setShowResult();
		void showStageEndResults(int score);//一小關卡結束，塞有提早打完的BOUNS分
		void showEndResults(int score);//整個關卡結束，塞最終得分

		int pauseButtionIndex = 0;
		int deadButtionIndex = 0;
		// 遊戲畫面的物件
		vector<CMovingBitmap> pauseButtons;
		vector<CMovingBitmap> deadButtons;

		CMovingBitmap pauseTitle;//遊戲暫停標題
		CMovingBitmap deadTitle_01;
		CMovingBitmap deadTitle_02;

		MovingObject playerArea;
		vector<CMovingBitmap> gameInterface;
		int TestPower = 16;
		int Bomb = 3;
		bool isDead = false;
		CMovingBitmap GreenStar;
		CMovingBitmap RedStar;
		vector<NumberDisplay> numberDisplays;
		int currentScore = 0;
		int maxScore = 1000000;
		vector<CMovingBitmap> interfaceBackgroundResource;
		NumberDisplay deadLivesShower;

		CMovingBitmap stageEndResults;//關卡結束畫面
		CMovingBitmap stageEndTitle;
		NumberDisplay stageEndBounsScores;
		CMovingBitmap stageClearText;

		CMovingBitmap endResults;//遊戲結束畫面
		NumberDisplay endScores;
		CMovingBitmap endTitle;


		// 玩家可交互物件
		float playerDelta = 7.0f;
		bool fire = false;
		std::shared_ptr<Player> player;
		bool isInvincibleCount = false;
		vector<MovingObject> playerBullets;
		vector<Enemy> enemies;
		vector<EnemyBullet> enemyBullets;
		vector<MovingObject> fallingObjects;
		void initGame();
		void showGame();
		void showBorder();
		void fixPlayerLocation();
		void checkBulletHitEnemy();
		void checkBulletHitBoss();
		void addFallingObject(MovingObject enemy);
		void updatePlayerBullet();
		void updateEnemy();
		void updateScore(int deltaScore);
		size_t frameCounter = 0;
		std::shared_ptr<Boss> boss;
		map<size_t, vector<MapData>> mapDatum;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}
