#include <algorithm>
#include <stdexcept>
#include "Map.h"

bool Map::addObject(std::unique_ptr<MapObject> &map_object) {
	Objects_.push_back(std::move(map_object));
	return true;
}

bool Map::removeObject(MapObject &map_object) {
	auto it = std::find_if(Objects_.begin(), Objects_.end(),
		[&map_object](const std::unique_ptr<MapObject>& ptr) {
			return ptr.get() == &map_object;
		});
	if (it != Objects_.end()) {
		Objects_.erase(it);
		return true;
	}
	return false;
}

MapObject& Map::operator[](size_t index) const {
	if (index >= Objects_.size()) {
		throw std::out_of_range("Index out of bounds!");
	}
	
	return *Objects_[index].get();
}

Point Map::getMapSize() const {
	return Size_;
}

size_t Map::getSize() const { 
	return Objects_.size(); 
}
