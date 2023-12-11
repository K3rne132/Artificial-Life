#pragma once
#include <memory>
#include "MapObject.h"
#include "Statistics.h"
#include "Movement.h"

class Animal : MapObject {
private:
	Statistics					_Statistics;
	std::unique_ptr<Movement>	_AnimalMovement;

public:
	bool isMoving();
};