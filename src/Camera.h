#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "SDL.h"
#include "PointBase.hpp"

class Camera {
private:
	float _Zoom;
	FPoint _Size;
	Point _MapSize;
	FPoint _Offset;
	FPoint _OldOffset;

	void adjustOffset() {
		const float MARGIN = 500.f;
		if (_Offset.X < -MARGIN)
			_Offset.X = -MARGIN;
		if (_Offset.Y < -MARGIN)
			_Offset.Y = -MARGIN;
		if (_Offset.X + _Size.X / _Zoom > _MapSize.X + MARGIN)
			_Offset.X = _MapSize.X - _Size.X / _Zoom + MARGIN;
		if (_Offset.Y + _Size.Y / _Zoom > _MapSize.Y + MARGIN)
			_Offset.Y = _MapSize.Y - _Size.Y / _Zoom + MARGIN;
	}

public:
	Camera(float width, float height, float map_width, float map_height) :
		_Zoom(1.f), _Size(width, height), _MapSize(map_width, map_height) {}

	float getZoom() { return _Zoom; }
	void setZoom(float zoom) {
		if (zoom < 0.5f)
			_Zoom = 0.5f;
		else if (zoom > 10.f)
			_Zoom = 10.f;
		else
			_Zoom = zoom;
		//FPoint old = _Size;
		//_Size.X = _Size.X / _Zoom;
		//_Size.Y = _Size.X / _Zoom;
		//_Offset += (old - _Size) / 2;
		//_OldOffset = _Offset;
		adjustOffset();
	}
	FPoint getOffset() {
		return _Offset;
	}
	FPoint getCenter() {
		return (_Offset + _Size) / 2;
	}
	void setMapSize(Point size) {
		_MapSize = size;
	}
	void setOffset(FPoint offset) {
		_Offset = _OldOffset + offset / _Zoom;
		adjustOffset();
	}
	void storeOffset() {
		_OldOffset = _Offset;
	}

};