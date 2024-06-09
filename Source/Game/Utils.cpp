#include "stdafx.h"
#include "Utils.h"

POINTF Utils::calculateXYSpeed(double angle, float speed)
{
	float x = (float)cos(angle * M_PI / 180) * speed;
	float y = (float)sin(angle * M_PI / 180) * speed;
	return POINTF{ x,y };
}

double Utils::angleToTarget(POINTF source, POINTF target)
{
	double angle2Target = 180 - atan2(target.y - source.y, source.x - target.x) * 180 / M_PI;
	return angle2Target;
}
