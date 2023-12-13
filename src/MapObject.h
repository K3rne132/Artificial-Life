#pragma once
#include "PointBase.hpp"
#include "Drawable.h"

class MapObject : public Drawable {
protected:
	Point _Position;

public:
	MapObject() : _Position(0, 0) {}
	MapObject(int x, int y) : _Position(x, y) {}
};