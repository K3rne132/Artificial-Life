#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"
#include "baseSize.hpp"

using Size = baseSize <int>;

class Map {
private:
	Size _Size;
	std::vector<std::unique_ptr<MapObject>> _Objects;

public:
	Map() : _Size(0, 0) {

	}

	Map(int width, int height) : _Size(width, height) {

	}

	bool addObject(std::unique_ptr<MapObject> &map_object);

	bool removeObject(MapObject &map_object);

	MapObject& operator[](size_t index);

	size_t getSize();
};
