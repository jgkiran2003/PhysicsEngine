#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
  public:
    float x, y;

    // Constructor: Sets x and y when you create the vector
    Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    // Rule: Adding two vectors together (like Position + Velocity)
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Rule: Multiplying by a number (like Velocity * Time)
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
};

#endif