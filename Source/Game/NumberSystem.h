#pragma once
#include <vector>
#include "../Library/gameutil.h"
#define MAX_DIGIT 10

using namespace game_framework;
using namespace std;

class NumberSystem
{
	int x = 0;
	int y = 0;
	int minDigit = 0;
	vector<CMovingBitmap> nums;

public:
	NumberSystem() = default;

	// getter
	int getX() { return this->x; };
	int getY() { return this->y; };

	// setter
	void setXY(int x, int y);
	void setMinDigit(int digit);

	void showNumber(int value);
	void onInit();
};

