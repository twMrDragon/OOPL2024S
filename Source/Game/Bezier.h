#pragma once
#include <vector>

class Bezier
{
private:
	std::vector<POINTF> points;
	POINTF calculatePointWithRatio(std::vector<POINTF> points,int currnetT,int splitCount);
public:
	Bezier()=default;
	Bezier(std::vector<POINTF> points);
	void setPoints(std::vector<POINTF> points);
	std::vector<POINTF> getEachPoint(int splitCount);
	std::vector<POINTF> getEachSpeed(int splitCount);
};

