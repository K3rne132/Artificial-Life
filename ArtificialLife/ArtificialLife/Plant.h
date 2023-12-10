#pragma once
#include "MapObject.h"

class Plant : MapObject {
private:
	float _NutritionalValue;

public:
	Plant() : _NutritionalValue(0.f) {

	}

	Plant(float nutritional_value) : _NutritionalValue(nutritional_value) {

	}
};