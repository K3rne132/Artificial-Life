#include <algorithm>
#include <stdexcept>
#include "Map.h"

bool Map::addObject(std::unique_ptr<MapObject> &map_object) {
	_Objects.push_back(std::move(map_object));
	return true;
}

bool Map::removeObject(MapObject &map_object) {
	auto it = std::find_if(_Objects.begin(), _Objects.end(),
		[&map_object](const std::unique_ptr<MapObject>& ptr) {
			return ptr.get() == &map_object;
		});
	if (it != _Objects.end()) {
		_Objects.erase(it);
		return true;
	}
	return false;
}

MapObject& Map::operator[](size_t index) const {
	if (index >= _Objects.size()) {
		throw std::out_of_range("Index out of bounds!");
	}
	
	return *_Objects[index].get();
}

Point Map::getMapSize() const {
	return _Size;
}

size_t Map::getSize() const { 
	return _Objects.size(); 
}
