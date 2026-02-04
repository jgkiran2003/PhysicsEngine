#include "Plane.h"
#include "BoundingSphere.h"

CollisionData Plane::IntersectSphere(const BoundingSphere& other) const {
  // Scalar projection of sphere center position vector onto unit normal
  float distanceFromOrigin = normal.Dot(other.GetCenter());

  // Shortest distance of sphere from plane
  float distanceFromPlane = distanceFromOrigin - distance;

  float penetrationDistance = other.GetRadius() - std::abs(distanceFromPlane);

  // Absolute value of distance of sphere from plane
  if (penetrationDistance > 0.0f) {
    Vector3 collisionNormal = (distanceFromPlane > 0) ? normal : normal * -1.0f;
    return CollisionData(true, collisionNormal, penetrationDistance);
  }

  return CollisionData(false);
}