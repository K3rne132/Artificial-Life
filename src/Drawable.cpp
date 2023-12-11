#include "Drawable.h"

void Drawable::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, _Color.r, _Color.g, _Color.b, _Color.a);
	SDL_RenderFillRectF(renderer, &_Rect);
}

void Drawable::draw(SDL_Renderer* renderer, SDL_FPoint offset) {
	SDL_FRect rect = _Rect;
	rect.x -= offset.x;
	rect.y -= offset.y;
	SDL_SetRenderDrawColor(renderer, _Color.r, _Color.g, _Color.b, _Color.a);
	SDL_RenderFillRectF(renderer, &rect);
}