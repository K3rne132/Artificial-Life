#pragma once
#include <SDL2/SDL.h>
#include "PointBase.hpp"

class Drawable {
public:
	virtual void draw(SDL_Renderer* renderer, FPoint offset = FPoint()) = 0;
};