#include "stdafx.h"
#include "ReimuB.h"

void ReimuB::showBall()
{
	ballR.SetTopLeft(int(getCenter().x) - 35, int(getCenter().y) - 10);
	ballR.ShowBitmap();

	ballL.SetTopLeft(int(getCenter().x) + 20, int(getCenter().y) - 10);
	ballL.ShowBitmap();
}

void ReimuB::onInit() {
	// ReumuB
	this->LoadBitmapByString(
		{ "Resources\\Image\\CM\\player00\\unshow.bmp",
		"Resources\\Image\\CM\\player00\\Sprite0.bmp",
		"Resources\\Image\\CM\\player00\\Sprite1.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite2.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite3.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite4.bmp" ,//4-10 left
		"Resources\\Image\\CM\\player00\\Sprite5.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite6.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite7.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite8.bmp" ,
		"Resources\\Image\\CM\\player00\\Sprite9.bmp" ,//	
		"Resources\\Image\\CM\\player00\\Sprite10.bmp" }, RGB(205, 205, 205));
	SetAnimation(100, false);//R L U D P
	initHitbox();
	setLocationF(200, 400);

	// animation setting
	setRangeAnimation(1, 3, 150, false);
	startToggleAnimation();

	// left ball setting
	ballL.LoadBitmapByString(
		{ "Resources\\Image\\CM\\player00\\Sprite12801.bmp",
		"Resources\\Image\\CM\\player00\\Sprite12802.bmp",
		"Resources\\Image\\CM\\player00\\Sprite12803.bmp",
		"Resources\\Image\\CM\\player00\\Sprite12804.bmp",
		}, RGB(205, 205, 205));

	ballL.SetAnimation(80, false);

	// right ball setting
	ballR.LoadBitmapByString(
		{ "Resources\\Image\\CM\\player00\\Sprite12804.bmp",
		"Resources\\Image\\CM\\player00\\Sprite12803.bmp",
		"Resources\\Image\\CM\\player00\\Sprite12802.bmp",
		"Resources\\Image\\CM\\player00\\Sprite12801.bmp",
		}, RGB(205, 205, 205));
	ballR.SetAnimation(80, false);
}

vector<MovingObject> ReimuB::attack()
{
	if (getPower() > 8) {
		firingIntervalIceBulletCounter++;
	}
	firingIntervalRedBulletCounter++;

	if (firingIntervalIceBulletCounter != firingIntervalIceBullet && firingIntervalRedBulletCounter != firingIntervalRedBullet) { return {}; }


	vector<MovingObject> totalBullets;
	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(0, 0, 0));
	bullet.setLocationF(getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
	bullet.setSpeedY((float)-15);

	if (getPower() < 8) {
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}
	}
	else if (getPower() < 16)
	{
		firingIntervalRedBullet = 4;
		firingIntervalIceBullet = 20;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}
		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - bullet.GetWidth() - 20, getCenter().y - 30);
			bullet.setSpeedX(0);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setLocationF(getCenter().x + bullet.GetWidth() + 10, getCenter().y - 30);
			totalBullets.push_back(bullet);
			firingIntervalIceBulletCounter = 0;
		}
	}
	else if (getPower() < 32)//
	{
		firingIntervalIceBullet = 15;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(0, 0, 0));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-0.45);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)0.45);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}

		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - bullet.GetWidth() - 20, getCenter().y - 30);
			bullet.setSpeedX(0);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setLocationF(getCenter().x + bullet.GetWidth() + 10, getCenter().y - 30);
			totalBullets.push_back(bullet);
			firingIntervalIceBulletCounter = 0;
		}
	}
	else if (getPower() < 48)
	{
		firingIntervalIceBullet = 11;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(0, 0, 0));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-0.45);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)0.45);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}

		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - bullet.GetWidth() - 20, getCenter().y - 30);
			bullet.setSpeedX(0);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setLocationF(getCenter().x + bullet.GetWidth() + 10, getCenter().y - 30);
			totalBullets.push_back(bullet);
			firingIntervalIceBulletCounter = 0;
		}

	}
	else if (getPower() < 64)
	{
		firingIntervalIceBullet = 11;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)//3shoot
		{
			totalBullets.push_back(bullet);
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(0, 0, 0));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-1.5);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)1.5);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}

		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - bullet.GetWidth() - 20, getCenter().y - 30);
			bullet.setSpeedX(0);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setLocationF(getCenter().x + bullet.GetWidth() + 10, getCenter().y - 30);
			totalBullets.push_back(bullet);


			firingIntervalIceBulletCounter = 0;
		}
	}
	else if (getPower() < 80)
	{
		firingIntervalIceBullet = 10;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)//3shoot
		{
			totalBullets.push_back(bullet);
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(0, 0, 0));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-1.5);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)1.5);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}

		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 10);
			bullet.setSpeedX(0);//30
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);


			//25
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);

			//yo
			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);//25


			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 10);
			totalBullets.push_back(bullet);



			firingIntervalIceBulletCounter = 0;
		}
	}
	else if (getPower() < 96)
	{
		firingIntervalIceBullet = 10;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)//3shoot
		{
			totalBullets.push_back(bullet);
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-1.5);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)1.5);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}

		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 10);
			bullet.setSpeedX(0);//30
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);


			//25
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);

			//yo
			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);//25


			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 10);
			totalBullets.push_back(bullet);



			firingIntervalIceBulletCounter = 0;
		}
	}
	else if (getPower() < 129)//
	{
		firingIntervalIceBullet = 10;
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			totalBullets.push_back(bullet);
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-1.5);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)1.5);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)3);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)-3);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}

		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 10);
			bullet.setSpeedX(0);//30
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);


			//25
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);

			//yo
			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);//25


			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 10);
			totalBullets.push_back(bullet);



			firingIntervalIceBulletCounter = 0;
		}
	}
	else {//Power MAX
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			totalBullets.push_back(bullet);
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(0, 0, 0));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-1.5);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)1.5);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)3);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)-3);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}
		if (firingIntervalIceBullet <= firingIntervalIceBulletCounter) {

			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite68.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y-30);
			bullet.setSpeedX(0);//30
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);


			//25
			bullet.setLocationF(getCenter().x - 35 + ballL.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);

			//yo
			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 + 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);//25


			bullet.setLocationF(getCenter().x + 20 + ballR.GetWidth() / 2 - bullet.GetWidth() - 2.5f, getCenter().y - 30);
			totalBullets.push_back(bullet);

			//center
			bullet.setLocationF(getCenter().x - 35 , getCenter().y - 30);
			totalBullets.push_back(bullet);

			bullet.setLocationF(getCenter().x + 20 , getCenter().y - 30);
			totalBullets.push_back(bullet);



			firingIntervalIceBulletCounter = 0;
		}
	}


	return totalBullets;
}

void ReimuB::spellCard()
{
}

void ReimuB::onShow()
{
	handMadeShow();
	if (power >= 8)
		showBall();
}
