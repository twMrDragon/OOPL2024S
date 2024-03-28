#pragma once
#include <vector>
#include "Point.h"

class Bezier
{
private:
	std::vector<Point> points;
	Point calculatePointWithRatio(std::vector<Point> points,int currnetT,int splitCount);
public:
	Bezier()=default;
	Bezier(std::vector<Point> points);
	void setPoints(std::vector<Point> points);
	std::vector<Point> getEachPoint(int splitCount);
	std::vector<Point> getEachSpeed(int splitCount);
};

