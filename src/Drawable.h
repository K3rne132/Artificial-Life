#pragma once
#include "SDL.h"

class Drawable {
private:
	SDL_FRect _Rect;
	SDL_Color _Color;

public:
	Drawable(SDL_FRect rect, SDL_Color color) :
		_Rect(rect), _Color(color) {}

	void draw(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, SDL_FPoint offset);
};