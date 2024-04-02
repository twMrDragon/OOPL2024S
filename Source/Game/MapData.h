#pragma once
#include "Point.h"
#include <vector>
#include <string>
using namespace std;
class MapData
{
public:
	vector<string> resource;
	COLORREF colorFilter;
	Point location;
	vector<Point> speeds;
};
