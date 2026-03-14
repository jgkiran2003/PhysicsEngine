#include "Collider.h"
#include "CollisionData.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include <iostream>

CollisionData Collider::Intersect(const Collider& other) const {
  if (type == TYPE_SPHERE && other.GetType() == TYPE_SPHERE) {
    BoundingSphere* self = (BoundingSphere*)this;
    return self->IntersectSphere((BoundingSphere&)other);
  }

  if (type == TYPE_SPHERE && other.GetType() == TYPE_PLANE) {
    BoundingSphere* self = (BoundingSphere*)this;
    CollisionData data = ((Plane&)other).IntersectSphere(*self);
    return CollisionData(data.DoesInteract(), data.GetDirection() * -1.0f, data.GetDistance());
  }

  if (type == TYPE_PLANE && other.GetType() == TYPE_SPHERE) {
    Plane* self = (Plane*)this;
    return self->IntersectSphere((BoundingSphere&)other);
  }

  if (type == TYPE_PLANE && other.GetType() == TYPE_PLANE) {
    return CollisionData(false);
  }


  // Error for combination that have not been implemented
  std::cerr << "Error: Collision math not implemented for these types." << std::endl;
  return CollisionData(false);
}