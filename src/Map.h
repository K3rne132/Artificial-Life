#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"

class Map {
private:
	Point Size_;
	std::vector<std::unique_ptr<MapObject>> Objects_;

public:
	Map() : Size_(0, 0) {}
	Map(int width, int height) : Size_(width, height) {}

	bool addObject(std::unique_ptr<MapObject>& map_object);
	bool removeObject(MapObject &map_object);
	auto begin() { return Objects_.begin(); }
	auto end() { return Objects_.end(); }
	MapObject& operator[](size_t index) const;
	Point getMapSize() const;
	size_t getSize() const;
};
