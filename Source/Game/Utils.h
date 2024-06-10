#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Utils
{
public:
	static POINTF calculateXYSpeed(double angle, float speed);
	static double angleToTarget(POINTF source, POINTF target);
};

