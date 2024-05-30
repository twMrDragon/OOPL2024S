#include "stdafx.h"
#include "Utils.h"

POINTF Utils::calculateXYSpeed(double angle, float speed)
{
	float x = (float)cos(angle * M_PI / 180) * speed;
	float y = (float)sin(angle * M_PI / 180) * speed;
	return POINTF{ x,y };
}
