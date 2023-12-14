#pragma once
#include "MapObject.h"

class Plant : MapObject {
private:
	float NutritionalValue_;

public:
	Plant() : NutritionalValue_(0.f) {}
	Plant(float nutritional_value) : NutritionalValue_(nutritional_value) {}
};