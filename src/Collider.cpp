#include "Collider.h"
#include "IntersectData.h"
#include "BoundingSphere.h"
#include <iostream>

IntersectData Collider::Intersect(const Collider& other) const {
  // Check if both objects are spheres
  if (type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE) {
    // Cast 'this' to a BoundingSphere to use its specific math
    BoundingSphere* self = (BoundingSphere*)this;
    return self->IntersectBoundingSphere((BoundingSphere&)other);
  }

  // Error for combination that have not been implemented
  std::cerr << "Error: Collision math not implemented for these types." << std::endl;
  return IntersectData(false, Vector2(0, 0));
}