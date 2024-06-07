#include "stdafx.h"
#include "BloodDisplay.h"

void BloodDisplay::setLocation(POINT location)
{
	this->location = location;
}

void BloodDisplay::setLocation(int x, int y)
{
	this->location.x = x;
	this->location.y = y;
}

void BloodDisplay::setWidth(int width)
{
	this->width = width;
}

void BloodDisplay::setHeight(int height)
{
	this->height = height;
}

POINT BloodDisplay::getLocation()
{
	return this->location;
}

void BloodDisplay::onShow(float ratio)
{
	for (int x = 0; x < (int)(width * ratio); x++)
	{
		for (int y = 0; y < height; y++)
		{
			bloodBitmap.SetTopLeft(this->location.x + x, this->location.y + y);
			bloodBitmap.ShowBitmap();
		}
	}
}

void BloodDisplay::onInit()
{
	this->bloodBitmap.LoadBitmapByString({ "Resources\\Image\\other\\boss_blood.bmp" });
}
