#pragma once
#include "SDL.h"
#include "PointBase.hpp"

class Drawable {
public:
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) = 0;
};