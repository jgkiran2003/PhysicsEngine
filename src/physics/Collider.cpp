#include "Collider.h"
#include "CollisionData.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include <iostream>

static CollisionData Flip(const CollisionData& data) {
  if (!data.DoesInteract()) return data;
  return CollisionData(true, data.GetDirection() * -1.0f, data.GetDistance());
}

CollisionData Collider::Intersect(const Collider& other) const {
  // Spheres
  if (type == TYPE_SPHERE) {
    if (other.GetType() == TYPE_SPHERE) {
      BoundingSphere* self = (BoundingSphere*)this;
      return self->IntersectSphere((BoundingSphere&)other);
    }

    if (other.GetType() == TYPE_PLANE) {
      BoundingSphere* self = (BoundingSphere*)this;
      CollisionData data = ((Plane&)other).IntersectSphere(*self);
      return Flip(data);
    }
  }

  // Plane
  if (type == TYPE_PLANE) {
    if (other.GetType() == TYPE_SPHERE) {
      Plane* self = (Plane*)this;
      return self->IntersectSphere((BoundingSphere&)other);
    }

    if (other.GetType() == TYPE_PLANE) {
      return CollisionData(false);
    }
  }


  // Error for combination that have not been implemented
  std::cerr << "Error: Collision math not implemented for these types." << std::endl;
  return CollisionData(false);
}