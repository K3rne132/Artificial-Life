#include "Animal.h"

bool Animal::isMoving() const {
	if (_AnimalMovement)
		return true;
	return false;
}

void Animal::draw(SDL_Renderer* renderer, FPoint offset){
	SDL_SetRenderDrawColor(renderer, 127, 187, 255, 255);
	SDL_FRect rect = {};
	rect.x = offset.X + _Position.X;
	rect.y = offset.Y + _Position.Y;
	rect.w = 10;
	rect.h = 10;
	SDL_RenderFillRectF(renderer, &rect);
}