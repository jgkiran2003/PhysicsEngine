#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
  public:
    float x, y, z;

    // Constructor: Sets x and y when you create the vector
    Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : 
      x(_x), y(_y), z(_z) {}

    // Returns length squared to avoid sqrt
    inline float LengthSquared() const {
        return x * x + y * y + z * z;
    }

    // Returns length of vector
    inline float Length() const {
        return std::sqrt(LengthSquared());
    }

    // Returns normalised vector
    Vector3 Normalized() const {
        float len = Length();
        if (len == 0) return Vector3(0, 0); // Prevent division by zero
        return Vector3(x / len, y / len, z / len);
    }

    // Rule: Adding two vectors together (like Position + Velocity)
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    //Rule: Subtracting another vector from this
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Rule: Multiplying by a number (like Velocity * Time)
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Rule: Dividing by a number
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Rule: Dot product of two vectors
    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

#endif