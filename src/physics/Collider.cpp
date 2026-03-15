#include "Collider.h"
#include "CollisionData.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "AABB.h"
#include <iostream>

static CollisionData Flip(const CollisionData& data) {
  if (!data.DoesInteract()) return data;
  return CollisionData(true, data.GetDirection() * -1.0f, data.GetDistance());
}

CollisionData Collider::Intersect(const Collider& other) const {
  // Spheres
  if (type == TYPE_SPHERE) {
    BoundingSphere* self = (BoundingSphere*)this;
    
    if (other.GetType() == TYPE_SPHERE) {
      return self->IntersectSphere((BoundingSphere&)other);
    }

    if (other.GetType() == TYPE_PLANE) {
      CollisionData data = ((Plane&)other).IntersectSphere(*self);
      return Flip(data);
    }

    if (other.GetType() == TYPE_AABB) {
      CollisionData data = ((AABB&)other).IntersectSphere(*self);
      return Flip(data);
    }
  }

  // Plane
  if (type == TYPE_PLANE) {
    Plane* self = (Plane*)this;

    if (other.GetType() == TYPE_SPHERE) {
      return self->IntersectSphere((BoundingSphere&)other);
    }

    if (other.GetType() == TYPE_PLANE) {
      return CollisionData(false);
    }

    if (other.GetType() == TYPE_AABB) {
      CollisionData data = ((AABB&)other).IntersectPlane(*self);
      return Flip(data);
    }
  }

  // AABB
  if (type == TYPE_AABB) {
    AABB* self = (AABB*)this;

    if (other.GetType() == TYPE_SPHERE) {
      return self->IntersectSphere((BoundingSphere&)other);
    }

    if (other.GetType() == TYPE_PLANE) {
      return self->IntersectPlane((Plane&)other);
    }

    if (other.GetType() == TYPE_AABB) {
      return self->IntersectAABB((const AABB&)other);
    }
  }

  // Error for combination that have not been implemented
  std::cerr << "Error: Collision math not implemented for these types." << std::endl;
  return CollisionData(false);
}