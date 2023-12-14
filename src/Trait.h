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

class Trait {
private:
    const float Min_, Max_;
    float Current_;

    float adjust(float value);

public:
    Trait(float min, float max, float current) : Min_(min), Max_(max), Current_(current) {}
    Trait(float min, float max) : Min_(min), Max_(max), Current_(min) {}

    inline operator float() const {
        return Current_;
    }

    inline Trait& operator+=(const float rhs) {
        Current_ = adjust(Current_ + rhs);
        return *this;
    }

    inline Trait& operator-=(const float rhs) {
        Current_ = adjust(Current_ - rhs);
        return *this;
    }

    inline Trait& operator=(const float rhs) {
        Current_ = adjust(rhs);
        return *this;
    }

    inline bool operator>(const float rhs) const {
        return Current_ > rhs;
    }

    inline bool operator<(const float rhs) const {
        return Current_ < rhs;
    }

    inline bool operator<=(const float rhs) const {
        return Current_ <= rhs;
    }

    inline bool operator>=(const float rhs) const {
        return Current_ >= rhs;
    }
};
