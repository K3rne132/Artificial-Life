#include "Animal.h"

bool Animal::isMoving() const {
	if (AnimalMovement_)
		return true;
	return false;
}

void Animal::draw(SDL_Renderer* renderer, FPoint offset){
	SDL_SetRenderDrawColor(renderer, 127, 187, 255, 255);
	SDL_FRect rect = {};
	rect.x = offset.X + Position_.X;
	rect.y = offset.Y + Position_.Y;
	rect.w = 10;
	rect.h = 10;
	SDL_RenderFillRectF(renderer, &rect);
}