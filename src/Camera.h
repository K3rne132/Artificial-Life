// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <SDL2/SDL.h>
#include "PointBase.hpp"

class Camera {
private:
	float Zoom_;
	FPoint Size_;
	Point MapSize_;
	FPoint Offset_;
	FPoint OldOffset_;

	void adjustOffset();

public:
	Camera() : Zoom_(1.f) {}

	// Return current zoom
	float getZoom() const;
	// Sets current zoom
	void setZoom(float zoom);
	// Returns difference between origin and present camera position
	FPoint getOffset() const;
	// Sets camera view in pixels
	void setCameraSize(FPoint size);
	// Updates max camera range
	void setMapSize(Point size);
	// Updates difference between origin and present camera position
	void setOffset(FPoint offset);
	// Stores temporary offset (used in map shifing)
	void storeOffset();
};
