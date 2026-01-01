#include "Collider.h"
#include "IntersectData.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include <iostream>

IntersectData Collider::Intersect(const Collider& other) const {
  // Check if both objects are spheres
  if (type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE) {
    BoundingSphere* self = (BoundingSphere*)this;
    return self->IntersectBoundingSphere((BoundingSphere&)other);
  }

  if (type == TYPE_SPHERE && other.GetType() == TYPE_PLANE) {
    BoundingSphere* self = (BoundingSphere*)this;
    return ((Plane&)other).IntersectSphere(*self);
  }

  if (type == TYPE_PLANE && other.GetType() == TYPE_SPHERE) {
    Plane* self = (Plane*)this;
    return self->IntersectSphere((BoundingSphere&)other);
  }

  if (type == TYPE_PLANE && other.GetType() == TYPE_PLANE) {
    return IntersectData(false, Vector2(0, 0));
  }


  // Error for combination that have not been implemented
  std::cerr << "Error: Collision math not implemented for these types." << std::endl;
  return IntersectData(false, Vector2(0, 0));
}