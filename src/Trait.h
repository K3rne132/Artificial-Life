#pragma once

class Trait {
private:
    const float Min_, Max_;
    float Current_;

    float adjust(float value) {
        if (value > Max_) {
            value = Max_;
        }
        else if (value < Min_) {
            value = Min_;
        }
        return value;
    }

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

    inline bool operator>(const float rhs) {
        return Current_ > rhs;
    }

    inline bool operator<(const float rhs) {
        return Current_ < rhs;
    }

    inline bool operator<=(const float rhs) {
        return Current_ <= rhs;
    }

    inline bool operator>=(const float rhs) {
        return Current_ >= rhs;
    }
};