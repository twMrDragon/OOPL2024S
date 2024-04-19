#include "stdafx.h"
#include "ReimuB.h"

void ReimuB::onInit() {
	LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite0.bmp" }, RGB(205, 205, 205));
	//setLocationF(200, 400);
	Player::onInit();
	invincible = 0;
	//ShowBitmap();
}

vector<MovingObject> ReimuB::attack()
{
	vector<MovingObject> totalBullets;



	MovingObject bullet;
	bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
	bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
	bullet.setSpeedY((float)-15);

	if (power < 8) {
		totalBullets.push_back(bullet);
	}
	else if (power < 16)
	{
		totalBullets.push_back(bullet);

	}
	else if (power < 32)//
	{
		totalBullets.push_back(bullet);
		for (int i = -10; i < 11; i=i+20)
		{
			MovingObject bullet;
			bullet.LoadBitmapByString({ "Resources\\Image\\CM\\player00\\Sprite69.bmp" }, RGB(205, 205, 205));
			bullet.setLocationF(getCenter().x + bullet.GetWidth() / 2.0f, getCenter().y + bullet.GetHeight() / 2.0f);
			bullet.setSpeedY((float)-15);
			bullet.setSpeedX((float)i);
			totalBullets.push_back(bullet);
		}

	}
	else if (power < 48)
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
	else if (power < 64)
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
	else if (power < 80)
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
	else if (power < 96)
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
	else if (power < 129)//
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
