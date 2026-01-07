#ifndef PLANE_H
#define PLANE_H

#include "Collider.h"
#include "Vector3.h"
#include "BoundingSphere.h"

class Plane : public Collider {
  public:
    Plane(const Vector3& normal, float distance) : 
      Collider(TYPE_PLANE),
      normal(normal.Normalized()),   
      distance(distance) {}

    // Collision with sphere
    CollisionData IntersectSphere(const BoundingSphere& other) const;

    virtual void Transform(const Vector3& translation) override {} // Static plane
    virtual Vector3 GetCenter() const override { return normal * distance; }

    inline const Vector3& GetNormal() const { return normal; }
    inline float GetDistance() const { return distance; }

  private:
    Vector3 normal; // Unit vector of normal from origin to plane
    float distance;
};

#endif