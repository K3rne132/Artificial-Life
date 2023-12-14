#pragma once
#include "PointBase.hpp"
#include "Drawable.h"

class MapObject : public Drawable {
protected:
	Point Position_;

public:
	MapObject() : Position_(0, 0) {}
	MapObject(int x, int y) : Position_(x, y) {}
};