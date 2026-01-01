#ifndef PLANE_H
#define PLANE_H

#include "Collider.h"
#include "Vector2.h"

// Forward declaration
class BoundingSphere;

class Plane : public Collider {
  public:
    Plane(const Vector2& normal, float distance) : 
      Collider(TYPE_PLANE),
      normal(normal.Normalized()),   
      distance(distance) {}

    // Collision with sphere
    IntersectData IntersectSphere(const BoundingSphere& other) const;

    virtual void Transform(const Vector2& translation) override {} // Static plane
    virtual Vector2 GetCenter() const override { return normal * distance; }

    inline const Vector2& GetNormal() const { return normal; }
    inline float GetDistance() const { return distance; }

  private:
    Vector2 normal;
    float distance;
};

#endif