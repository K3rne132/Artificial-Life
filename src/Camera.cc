// Copyright (C) 2023  Mateusz Jurczak & Julia Parobczy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.



#include "Camera.h"

void Camera::adjustOffset() {
	const float MARGIN = 500.f;
	if (Offset_.X < -MARGIN)
		Offset_.X = -MARGIN;
	if (Offset_.Y < -MARGIN)
		Offset_.Y = -MARGIN;
	if (Offset_.X + Size_.X / Zoom_ > MapSize_.X + MARGIN)
		Offset_.X = MapSize_.X - Size_.X / Zoom_ + MARGIN;
	if (Offset_.Y + Size_.Y / Zoom_ > MapSize_.Y + MARGIN)
		Offset_.Y = MapSize_.Y - Size_.Y / Zoom_ + MARGIN;
}

float Camera::getZoom() const {
	return Zoom_;
}

void Camera::setZoom(float zoom) {
	if (zoom < 0.2f)
		Zoom_ = 0.2f;
	else if (zoom > 10.f)
		Zoom_ = 10.f;
	else
		Zoom_ = zoom;
	//FPoint old = _Size;
	//_Size.X = _Size.X / _Zoom;
	//_Size.Y = _Size.X / _Zoom;
	//_Offset += (old - _Size) / 2;
	//_OldOffset = _Offset;
	adjustOffset();
}

FPoint Camera::getOffset() const {
	return Offset_;
}

void Camera::setCameraSize(FPoint size) {
	Size_ = size;
}

void Camera::setMapSize(Point size) {
	MapSize_ = size;
}

void Camera::setOffset(FPoint offset) {
	Offset_ = OldOffset_ + offset / Zoom_;
	adjustOffset();
}

void Camera::storeOffset() {
	OldOffset_ = Offset_;
}
