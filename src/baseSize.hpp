#pragma once

template <typename T>
class baseSize {
public:
	int Width, Height;

	baseSize() : Width(0), Height(0) {

	}

	baseSize(T width, T height) : Width(width), Height(height) {

	}

	inline baseSize& operator=(const baseSize& rhs) {
		Width = rhs.Width;
		Height = rhs.Height;
		return *this;
	}
};
