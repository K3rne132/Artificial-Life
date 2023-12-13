#pragma once
#include "Trait.h"

class Statistics {
private:
	Trait t1;
	Trait t2;
	Trait t3;

public:
	Statistics() : t1(0.f, 1.f), t2(0.f, 1.f), t3(0.f, 1.f) {}
};