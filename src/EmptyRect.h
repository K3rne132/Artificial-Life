#pragma once
#include "Shape.h"

class EmptyRect : public Shape {
public:
	EmptyRect(SDL_FRect rect, SDL_Color color) : Shape(rect, color) {}

	virtual void draw(SDL_Renderer* renderer, FPoint offset) override {
		SDL_SetRenderDrawColor(renderer, Color_.r, Color_.g, Color_.b, Color_.a);
		SDL_FRect rect = Rect_;
		rect.x += offset.X;
		rect.y += offset.Y;
		SDL_RenderDrawRectF(renderer, &rect);
	}
};