// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include <chrono>
#include "Simulation.h"
#include "FilledRect.h"
#include "Colors.h"
#include "TextInput.h"
#include "Animal.h"
#include "Window.h"
#include "Plant.h"
#include "Random.h"

void Simulation::generatePlant(long long milliseconds) {
	TimeElapsedPlant_ += milliseconds;
	while (TimeElapsedPlant_ > PlantGeneration_) {
		if (Plant::Count < 2048) {
			float x = getRandomFloat(Map_.getMapSize().X);
			float y = getRandomFloat(Map_.getMapSize().Y);
			auto plant = std::unique_ptr<Drawable>(new Plant(FPoint(x, y)));
			Map_.addObject(std::move(plant));
		}
		TimeElapsedPlant_ -= PlantGeneration_;
	}
}

void Simulation::updateAnimals() {
	for (size_t i = 0; i < Map_.getSize(); ++i) {
		Animal* anim = dynamic_cast<Animal*>(&Map_[i]);
		if (anim)
			anim->updateNearest();
	}
}

void Simulation::moveAnimals(long long milliseconds) {
	for (size_t i = 0; i < Map_.getSize(); ++i) {
		Animal* animal = dynamic_cast<Animal*>(&Map_[i]);
		if (animal) {
			animal->move(milliseconds);
		}
	}
}

void Simulation::synchronize(long long milliseconds) {
	if (Speed_ > 0.001f) {
		//updateAnimals();
		moveAnimals(milliseconds);
		generatePlant(milliseconds);
	}
}

void Simulation::dispatchEvent() {
	switch (Event_.type) {
	case SDL_QUIT:
		Quit_ = true;
		break;
	//case SDL_WINDOWEVENT:
	//	if (Event_.window.event == SDL_WINDOWEVENT_RESIZED) {
	//		Window_.scaleWindow(Event_.window.data1, Event_.window.data2);
	//	}
	//	break;
	case SDL_MOUSEWHEEL:
		Controls_.mouseWheel(Event_.wheel.y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		Controls_.mouseButtonDown(Event_.button.button);
		break;
	case SDL_MOUSEMOTION:
		Controls_.mouseMotion();
		break;
	case SDL_MOUSEBUTTONUP:
		Controls_.mouseButtonUp(Event_.button.button);
		break;
	case SDL_KEYDOWN:
		Controls_.keyPressed(Event_.key.keysym.sym);
		break;
	case SDL_TEXTINPUT:
		Controls_.textInput(Event_.text.text);
		break;
	}
}

void Simulation::addMapBorder() {
	SDL_FRect dest = {};
	dest.w = Map_.getMapSize().X;
	dest.h = Map_.getMapSize().Y;
	auto border = std::unique_ptr<Drawable>(new FilledRect(dest, WHITE));
	Window_.setBorder(border);
}

void Simulation::resetCamera() {
	Camera_.setMapSize(Map_.getMapSize());
	Camera_.setCameraSize(Window_.getWindowSize());
}

void Simulation::updateMap() {
	addMapBorder();
	resetCamera();
}

void Simulation::zoomIn() {
	Camera_.setZoom(Camera_.getZoom() * 1.15f);
}

void Simulation::zoomOut() {
	Camera_.setZoom(Camera_.getZoom() * 0.9f);
}

void Simulation::speedUp() {
	if (Speed_ < 1.f)
		Speed_ += 0.1f;
	else if (Speed_ < 5.f)
		Speed_ += 0.5f;
	else if (Speed_ < 10.f)
		Speed_ += 1.f;
	else if (Speed_ < 20.f)
		Speed_ += 2.f;
	else
		Speed_ += 5.f;
	if (Speed_ >= 50.f)
		Speed_ = 50.f;
}

void Simulation::speedDown() {
	if (Speed_ < 1.5f)
		Speed_ -= 0.1f;
	else if (Speed_ < 5.5f)
		Speed_ -= 0.5f;
	else if (Speed_ < 11.f)
		Speed_ -= 1.f;
	else if (Speed_ < 22.f)
		Speed_ -= 2.f;
	else
		Speed_ -= 5.f;
	if (Speed_ <= 0.f)
		Speed_ = 0.f;
}

void Simulation::pause() {
	if (Speed_ > 0.001f)
		StoredSpeed_ = Speed_;
	Speed_ = 0.f;
}

void Simulation::resume() {
	if (Speed_ > 0.001f)
		return;
	Speed_ = StoredSpeed_;
}

void Simulation::moveCamera(float x, float y) {
	moveCamera(FPoint(x, y));
}

void Simulation::moveCamera(FPoint offset) {
	Camera_.setOffset(offset);
}

void Simulation::stopMoveCamera() {
	Camera_.storeOffset();
}

void Simulation::launch() {
	auto begin = std::chrono::steady_clock::now();
	while (!Quit_) {
		while (SDL_PollEvent(&Event_)) {
			dispatchEvent();
		}
		Window_.render(*this);
		auto now = std::chrono::steady_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
		long long ms_elapsed = diff.count() * Speed_;
		synchronize(ms_elapsed);
		begin = now;
		highlightSelectedAnimal();
		SDL_Delay(16); // 60fps
	}
}

bool Simulation::addMapObject(std::unique_ptr<Drawable>& map_object) {
	return Map_.addObject(std::move(map_object));
}

void Simulation::removeSelectedAnimal() {
	if (AnimalSelected_)
		Map_.removeObject(*AnimalSelected_);
}

void Simulation::highlightSelectedAnimal() {
	if (AnimalSelected_) {
		SDL_FRect rect;
		rect.x = AnimalSelected_->getPosition().X;
		rect.y = AnimalSelected_->getPosition().Y;
		rect.w = AnimalSelected_->getRealSize().X;
		rect.h = AnimalSelected_->getRealSize().Y;
		EmptyRect highlight = EmptyRect(rect, BLACK);
		highlight.draw(Window_, !Camera_.getOffset());
	}
}

void Simulation::bindAnimalStatistics(Animal& animal) {
	Menu_.bindStatistics(animal);
}

void Simulation::toggleMainMenu() {
	if (MainMenuHidden_) {
		showMainMenu();
		MainMenuHidden_ = false;
	}
	else {
		hideMainMenu();
		MainMenuHidden_ = true;
	}
}

void Simulation::hideMainMenu() {
	for (auto& elem : Menu_) {
		if (elem->getGroup() == ButtonGroup::MAINMENU)
			elem->hide();
	}
}

void Simulation::showMainMenu() {
	for (auto& elem : Menu_) {
		if (elem->getGroup() == ButtonGroup::MAINMENU)
			elem->show();
	}
}
void Simulation::hideAnimalMenu() {
	for (auto& elem : Menu_) {
		if (elem->getGroup() == ButtonGroup::ANIMALMENU)
			elem->hide();
	}
}

void Simulation::showAnimalMenu() {
	for (auto& elem : Menu_) {
		if (elem->getGroup() == ButtonGroup::ANIMALMENU)
			elem->show();
	}
}

void Simulation::select(Button& button) {
	unselectAll();
	button.whenSelected();
	ButtonSelected_ = &button;
}

void Simulation::select(TextInput& input) {
	unselectAll();
	input.whenSelected();
	TextInputSelected_ = &input;
}

void Simulation::select(Animal& animal) {
	unselectAll();
	animal.whenSelected();
	AnimalSelected_ = &animal;
}

void Simulation::unselect(Button& button) {
	if (ButtonSelected_ == &button) {
		ButtonSelected_->whenUnselected();
		ButtonSelected_ = nullptr;
	}
}
void Simulation::unselect(TextInput& input) {
	if (TextInputSelected_ == &input) {
		TextInputSelected_->whenUnselected();
		TextInputSelected_ = nullptr;
	}
}
void Simulation::unselect(Animal& animal) {
	if (AnimalSelected_ == &animal) {
		AnimalSelected_->whenUnselected();
		AnimalSelected_ = nullptr;
	}
}

void Simulation::unselectAll() {
	if (ButtonSelected_)
		ButtonSelected_->whenUnselected();
	ButtonSelected_ = nullptr;
	if (TextInputSelected_)
		TextInputSelected_->whenUnselected();
	TextInputSelected_ = nullptr;
	if (AnimalSelected_)
		AnimalSelected_->whenUnselected();
	AnimalSelected_ = nullptr;
}
