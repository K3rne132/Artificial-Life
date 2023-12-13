#pragma once
#include "Drawable.h"

class Shape : public Drawable {
protected:
	SDL_FRect _Rect;
	SDL_Color _Color;

public:
	Shape() : _Rect(SDL_FRect()), _Color(SDL_Color()) {}
	Shape(SDL_FRect rect, SDL_Color color) : _Rect(rect), _Color(color) {}
};