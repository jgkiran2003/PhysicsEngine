#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2 {
  public:
    float x, y;

    // Constructor: Sets x and y when you create the vector
    Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    // Returns length squared to avoid sqrt
    inline float LengthSquared() const {
        return x * x + y * y;
    }

    // Returns length of vector
    inline float Length() const {
        return std::sqrt(LengthSquared());
    }

    // Returns normalised vector
    Vector2 Normalized() const {
        float len = Length();
        if (len == 0) return Vector2(0, 0); // Prevent division by zero
        return Vector2(x / len, y / len);
    }

    // Rule: Adding two vectors together (like Position + Velocity)
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    //Rule: Subtracting another vector from this
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Rule: Multiplying by a number (like Velocity * Time)
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
};

#endif