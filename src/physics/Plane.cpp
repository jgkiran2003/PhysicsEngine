#include "Plane.h"
#include "BoundingSphere.h"

CollisionData Plane::IntersectSphere(const BoundingSphere& other) const {
  // Scalar projection of sphere center position vector onto unit normal
  float distanceFromOrigin = normal.Dot(other.GetCenter());

  // Shortest distance of sphere from plane
  float distanceFromPlane = distanceFromOrigin - distance;

  // Absolute value of distance of sphere from plane
  if (std::abs(distanceFromPlane) < other.GetRadius()) {
    Vector3 collisionNormal = (distanceFromPlane > 0) ? normal : normal * -1.0f;
    return CollisionData(true, collisionNormal);
  }

  return CollisionData(false, Vector3(0, 0, 0));
}