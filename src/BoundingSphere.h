#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "Collider.h"
#include "Vector2.h"

class BoundingSphere : public Collider {
  public:
    BoundingSphere(const Vector2& center, float radius) :
      Collider(Collider::TYPE_SPHERE),
      center(center), 
      radius(radius) {}

    // Math for collision with another bounding sphere
    IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

    // Overriding base class function
    virtual void Transform(const Vector2& translation) override;
    virtual Vector2 GetCenter() const override { return center; }
    
    virtual float GetRadius() const { return radius; }

  private:
    Vector2 center;
    float radius;
};

#endif