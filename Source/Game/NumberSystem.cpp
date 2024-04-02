#include "stdafx.h"
#include "NumberSystem.h"

NumberSystem::NumberSystem() {
	vector<vector<string>> numbersImagePath = {
		{"Resources\\Image\\IN\\ascii\\Sprite27.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite28.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite29.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite30.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite31.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite32.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite33.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite34.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite35.bmp"},
		{"Resources\\Image\\IN\\ascii\\Sprite36.bmp"},
	};

	for (size_t i = 0; i < numbersImagePath.size(); i++)
	{
		CMovingBitmap num;
		num.LoadBitmapByString(numbersImagePath[i], RGB(0, 0, 0));
		this->nums.push_back(num);
	}
}

void NumberSystem::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void NumberSystem::setMinDigit(int digit) {
	this->minDigit = digit;
}

void NumberSystem::showNumber(int value) {
	bool flag = false;
	int dx = -2;
	int dividend = 1;
	for (int i = 0; i < MAX_DIGIT - 1; i++)
		dividend *= 10;

	int rollingX = this->x;
	for (int i = MAX_DIGIT - 1; i >= 0; i--)
	{
		int digit = value / dividend % 10;
		if (digit != 0)
			flag = true;
		if (flag || i < minDigit || i == 0) {
			CMovingBitmap num = this->nums[digit];
			num.SetTopLeft(rollingX, this->y);
			num.ShowBitmap();
			rollingX += (num.GetWidth() + dx);
		}

		dividend /= 10;
	}
}