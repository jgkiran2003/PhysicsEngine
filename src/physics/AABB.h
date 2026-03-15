#ifndef AABB_H
#define AABB_H

#include "Collider.h"
#include "Vector3.h"
#include "BoundingSphere.h"

class AABB: public Collider {
  // Axis-Aligned Bounding Box (AABB) for efficient collision calculation
  public:
    AABB(const Vector3& min, const Vector3& max) : 
      Collider(Collider::TYPE_AABB),
      min(min), 
      max(max) {}

    CollisionData IntersectAABB(const AABB& other) const;
    CollisionData IntersectSphere(const BoundingSphere& sphere) const;

    void Transform(const Vector3& t) override { min = min + t; max = max + t; }
    Vector3 GetCenter() const override { return (min + max) * 0.5f; }

    Vector3 GetHalfExtents() const { return (max - min) * 0.5f; }
    Vector3 GetMin() const { return min; }
    Vector3 GetMax() const { return max; }

  private:
    Vector3 min, max;
};

#endif