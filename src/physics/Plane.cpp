#include "Plane.h"
#include "BoundingSphere.h"

IntersectData Plane::IntersectSphere(const BoundingSphere& other) const {
  // Distance of sphere center from origin
  float distanceFromOrigin = normal.Dot(other.GetCenter());

  // Shortest distance of sphere from plane
  float distanceFromPlane = distanceFromOrigin - distance;

  // Check for collision
  if (distanceFromPlane < other.GetRadius()) {
    return IntersectData(true, normal * (other.GetRadius() - distanceFromPlane));
  }

  return IntersectData(false, Vector2(0, 0));
}