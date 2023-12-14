#pragma once
#include <memory>
#include "MapObject.h"
#include "Statistics.h"
#include "Movement.h"

class Animal : public MapObject {
private:
	Statistics                Statistics_;
	std::unique_ptr<Movement> AnimalMovement_;

public:
	Animal() {}
	Animal(int x, int y) : MapObject(x, y) {}

	bool isMoving() const;
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) override;
};
