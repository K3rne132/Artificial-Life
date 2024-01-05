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

	float getZoom() const;
	void setZoom(float zoom);
	FPoint getOffset() const;
	FPoint getCenter() const;
	void setCameraSize(FPoint size);
	void setMapSize(Point size);
	void setOffset(FPoint offset);
	void storeOffset();
};
