#include "stdafx.h"
#include "Bezier.h"

Bezier::Bezier(std::vector<Point> points) {
	this->points = points;
}

void Bezier::setPoints(std::vector<Point> points) {
	this->points = points;
}

Point Bezier::calculatePointWithRatio(std::vector<Point> points, int currnetT, int splitCount) {
	if (points.size() == 1)
		return points[0];
	std::vector<Point> descendingPoints;
	for (size_t i = 1; i < points.size(); i++) {
		Point p;
		p.x = (points[i].x - points[i - 1].x) * currnetT / splitCount + points[i - 1].x;
		p.y = (points[i].y - points[i - 1].y) * currnetT / splitCount + points[i - 1].y;
		descendingPoints.push_back(p);
	}
	return calculatePointWithRatio(descendingPoints, currnetT, splitCount);
}

std::vector<Point> Bezier::getEachPoint(int splitCount) {
	std::vector<Point> points;
	for (int i = 0; i < splitCount; i++)
		points.push_back(calculatePointWithRatio(this->points, i, splitCount - 1));
	return points;
}

std::vector<Point> Bezier::getEachSpeed(int splitCount) {
	std::vector<Point> points = getEachPoint(splitCount);
	std::vector<Point> speeds;
	speeds.push_back(Point(0, 0));
	for (size_t i = 1; i < points.size(); i++)
	{
		Point p;
		p.x = points[i].x - points[i - 1].x;
		p.y = points[i].y - points[i - 1].y;
		speeds.push_back(p);
	}
	return speeds;
}