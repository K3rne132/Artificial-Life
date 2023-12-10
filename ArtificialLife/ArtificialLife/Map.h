#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"

class Map {
private:
	int _Width, _Height;
	std::vector<std::unique_ptr<MapObject>> _Objects;

public:
	Map() : _Width(0), _Height(0) {

	}

	Map(int width, int height) : _Width(width), _Height(height) {

	}

	bool addObject(std::unique_ptr<MapObject> &map_object);

	bool removeObject(MapObject &map_object);

	MapObject& operator[](size_t index);

	size_t getSize();
};
