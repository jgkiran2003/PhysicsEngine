#include "BoundingSphere.h"

CollisionData BoundingSphere::IntersectSphere(const BoundingSphere& other) const {

  float radiusSum = radius + other.GetRadius();
  // Distance between centers
  Vector3 centersVector = other.GetCenter() - center;
  float centerDistance = centersVector.Length();
  // Penetration distance
  float penetrationDistance = radiusSum - centerDistance;

  // Check for overlap
  if (penetrationDistance > 0.0f) {
    return CollisionData(true, centersVector.Normalized(), penetrationDistance);
  }

  // No collision
  return CollisionData(false);
};

void BoundingSphere::Transform(const Vector3& translation) {
  center = center + translation;
}