#pragma once
#include "Shape.h"

class EmptyRect : public Shape {
public:
	EmptyRect(SDL_FRect rect, SDL_Color color) : Shape(rect, color) {}

	virtual void draw(SDL_Renderer* renderer, FPoint offset) override {
		SDL_SetRenderDrawColor(renderer, _Color.r, _Color.g, _Color.b, _Color.a);
		SDL_FRect rect = _Rect;
		rect.x += offset.X;
		rect.y += offset.Y;
		SDL_RenderDrawRectF(renderer, &rect);
	}
};