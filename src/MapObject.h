#pragma once
#include "basePoint.hpp"
using Point = basePoint<int>;

class MapObject {
private:
	Point _Point;

public:
	MapObject() : _Point(0, 0) {

	}

	MapObject(int x, int y) : _Point(x, y) {
	
	}
};