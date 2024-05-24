#include "stdafx.h"
#include "ReimuB.h"

void ReimuB::onInit() {
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
	//setLocationF(200, 400);
	Player::onInit();

	ShowBitmap();
}

vector<MovingObject> ReimuB::attack()
{
	firingIntervalIceBulletCounter++;
	firingIntervalRedBulletCounter++;

	if (firingIntervalIceBulletCounter != firingIntervalIceBullet && firingIntervalRedBulletCounter != firingIntervalRedBullet) { return {}; }


	vector<MovingObject> totalBullets;
	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
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
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}
	}
	else if (getPower() < 32)//
	{
		if (firingIntervalRedBullet == firingIntervalRedBulletCounter)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(-0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			bullet.setSpeedX((float)-0.45);
			bullet.setSpeedY((float)-15);
			totalBullets.push_back(bullet);

			bullet.setSpeedX((float)0.45);
			bullet.setLocationF(0.5f + getCenter().x - bullet.GetWidth() / 2.0f, getCenter().y - bullet.GetHeight() / 2.0f);
			totalBullets.push_back(bullet);
			firingIntervalRedBulletCounter = 0;
		}
	}
	else if (getPower() < 48)
	{


	}
	else if (getPower() < 64)
	{
		totalBullets.push_back(bullet);
		for (int i = -10; i < 11; i = i + 20)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
			bullet.setSpeedY((float)-15);
			bullet.setSpeedX((float)i);
			totalBullets.push_back(bullet);
		}
	}
	else if (getPower() < 80)
	{
		totalBullets.push_back(bullet);
		for (int i = -10; i < 11; i = i + 20)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
			bullet.setSpeedY((float)-15);
			bullet.setSpeedX((float)i);
			totalBullets.push_back(bullet);
		}
	}
	else if (getPower() < 96)
	{
		totalBullets.push_back(bullet);
		for (int i = -10; i < 11; i = i + 20)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
			bullet.setSpeedY((float)-15);
			bullet.setSpeedX((float)i);
			totalBullets.push_back(bullet);
		}
	}
	else if (getPower() < 129)//
	{
		for (int i = -20; i < 21; i = i + 10)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
			bullet.setSpeedY((float)-15);
			bullet.setSpeedX((float)i);
			totalBullets.push_back(bullet);
		}
	}
	else {//Power MAX
		for (int i = -20; i < 21; i = i + 10)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
			bullet.setSpeedY((float)-15);
			bullet.setSpeedX((float)i);
			totalBullets.push_back(bullet);
		}
	}

	return totalBullets;
}

void ReimuB::spellCard()
{
}
