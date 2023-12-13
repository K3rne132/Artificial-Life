#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"

class Map {
private:
	Point _Size;
	std::vector<std::unique_ptr<MapObject>> _Objects;

public:
	Map() : _Size(0, 0) {}
	Map(int width, int height) : _Size(width, height) {}

	bool addObject(std::unique_ptr<MapObject>& map_object);
	bool removeObject(MapObject &map_object);
	auto begin() { return _Objects.begin(); }
	auto end() { return _Objects.end(); }
	MapObject& operator[](size_t index) const;
	Point getMapSize() const;
	size_t getSize() const;
};
