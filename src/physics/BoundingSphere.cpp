#include "BoundingSphere.h"

CollisionData BoundingSphere::IntersectSphere(const BoundingSphere& other) const {
  // Sum of radii
  float radiusSum = radius + other.GetRadius();
  // Distance between centers
  Vector3 centersVector = other.GetCenter() - center;
  float centerDistance = centersVector.Length();
  
  // Check for ovelap
  if (centerDistance < radiusSum) {
    return CollisionData(true, centersVector.Normalized());
  }

  // No collision
  return CollisionData(false, Vector3(0, 0));
};

void BoundingSphere::Transform(const Vector3& translation) {
  center = center + translation;
}