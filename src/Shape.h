#pragma once
#include "Drawable.h"

class Shape : public Drawable {
protected:
	SDL_FRect Rect_;
	SDL_Color Color_;

public:
	Shape() : Rect_(SDL_FRect()), Color_(SDL_Color()) {}
	Shape(SDL_FRect rect, SDL_Color color) : Rect_(rect), Color_(color) {}
};