#include "Plane.h"
#include "BoundingSphere.h"

IntersectData Plane::IntersectSphere(const BoundingSphere& other) const {
  // Scalar projection of sphere center position vector onto unit normal
  float distanceFromOrigin = normal.Dot(other.GetCenter());

  // Shortest distance of sphere from plane
  float distanceFromPlane = distanceFromOrigin - distance;

  // Absolute value of distance of sphere from plane
  if (std::abs(distanceFromPlane) < other.GetRadius()) {
    float overlap = other.GetRadius() - std::abs(distanceFromPlane);
    
    // The direction depends on which side it hit
    Vector2 collisionNormal = (distanceFromPlane > 0) ? normal : normal * -1.0f;
    return IntersectData(true, collisionNormal * overlap);
  }

  return IntersectData(false, Vector2(0, 0));
}