#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "Collider.h"
#include "Vector3.h"

class BoundingSphere : public Collider {
  public:
    BoundingSphere(const Vector3& center, float radius) :
      Collider(Collider::TYPE_SPHERE),
      center(center), 
      radius(radius) {}

    // Math for collision with another bounding sphere
    IntersectData IntersectSphere(const BoundingSphere& other) const;

    // Overriding base class function
    virtual void Transform(const Vector3& translation) override;
    virtual Vector3 GetCenter() const override { return center; }
    
    virtual float GetRadius() const { return radius; }

  private:
    Vector3 center;
    float radius;
};

#endif