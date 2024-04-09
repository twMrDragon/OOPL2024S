#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(std::vector<POINTF> points) {
	this->points = points;
}

void Bezier::setPoints(std::vector<POINTF> points) {
	this->points = points;
}

POINTF Bezier::calculatePointWithRatio(std::vector<POINTF> points, int currnetT, int splitCount) {
	if (points.size() == 1)
		return points[0];
	std::vector<POINTF> descendingPoints;
	for (size_t i = 1; i < points.size(); i++) {
		POINTF p;
		p.x = (points[i].x - points[i - 1].x) * currnetT / splitCount + points[i - 1].x;
		p.y = (points[i].y - points[i - 1].y) * currnetT / splitCount + points[i - 1].y;
		descendingPoints.push_back(p);
	}
	return calculatePointWithRatio(descendingPoints, currnetT, splitCount);
}

std::vector<POINTF> Bezier::getEachPoint(int splitCount) {
	std::vector<POINTF> points;
	for (int i = 0; i < splitCount; i++)
		points.push_back(calculatePointWithRatio(this->points, i, splitCount - 1));
	return points;
}

std::vector<POINTF> Bezier::getEachSpeed(int splitCount) {
	std::vector<POINTF> points = getEachPoint(splitCount);
	std::vector<POINTF> speeds;
	speeds.push_back(POINTF{ 0,0 });
	for (size_t i = 1; i < points.size(); i++)
	{
		POINTF p;
		p.x = points[i].x - points[i - 1].x;
		p.y = points[i].y - points[i - 1].y;
		speeds.push_back(p);
	}
	return speeds;
}