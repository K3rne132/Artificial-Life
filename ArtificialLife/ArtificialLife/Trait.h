#pragma once

class Trait {
private:
    const float _Min, _Max;
    float _Current;

    float adjust(float value) {
        if (value > _Max) {
            value = _Max;
        }
        else if (value < _Min) {
            value = _Min;
        }
        return value;
    }

public:
    Trait(float min, float max, float current) : _Min(min), _Max(max), _Current(current) {

    }

    Trait(float min, float max) : _Min(min), _Max(max), _Current(min) {

    }

    inline operator float() const {
        return _Current;
    }

    inline Trait& operator+=(const float rhs) {
        _Current = adjust(_Current + rhs);
        return *this;
    }

    inline Trait& operator-=(const float rhs) {
        _Current = adjust(_Current - rhs);
        return *this;
    }

    inline Trait& operator=(const float rhs) {
        _Current = adjust(rhs);
        return *this;
    }

    inline bool operator>(const float rhs) {
        return _Current > rhs;
    }

    inline bool operator<(const float rhs) {
        return _Current < rhs;
    }

    inline bool operator<=(const float rhs) {
        return _Current <= rhs;
    }

    inline bool operator>=(const float rhs) {
        return _Current >= rhs;
    }
};