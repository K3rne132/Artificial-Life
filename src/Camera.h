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

	void adjustOffset() {
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

public:
	Camera(float width, float height, float map_width, float map_height) :
		Zoom_(1.f), Size_(width, height), MapSize_(map_width, map_height) {}

	float getZoom() { return Zoom_; }
	void setZoom(float zoom) {
		if (zoom < 0.5f)
			Zoom_ = 0.5f;
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
	FPoint getOffset() {
		return Offset_;
	}
	FPoint getCenter() {
		return (Offset_ + Size_) / 2;
	}
	void setMapSize(Point size) {
		MapSize_ = size;
	}
	void setOffset(FPoint offset) {
		Offset_ = OldOffset_ + offset / Zoom_;
		adjustOffset();
	}
	void storeOffset() {
		OldOffset_ = Offset_;
	}

};