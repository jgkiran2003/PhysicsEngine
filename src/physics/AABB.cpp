#include "AABB.h"
#include <algorithm>

CollisionData AABB::IntersectAABB(const AABB& other) const {
    // Overlap on each axis
    float overlapX = std::min(max.x, other.max.x) - std::max(min.x, other.min.x);
    float overlapY = std::min(max.y, other.max.y) - std::max(min.y, other.min.y);
    float overlapZ = std::min(max.z, other.max.z) - std::max(min.z, other.min.z);

    if (overlapX <= 0 || overlapY <= 0 || overlapZ <= 0)
        return CollisionData(false);

    // Normal force aligns with the shallowest axis
    float minOverlap = std::min({overlapX, overlapY, overlapZ});
    Vector3 normal;
    if (minOverlap == overlapX) normal = Vector3(1,0,0);
    else if (minOverlap == overlapY) normal = Vector3(0,1,0);
    else normal = Vector3(0,0,1);

    // Push A away from B's center
    Vector3 dir = other.GetCenter() - GetCenter();
    if (normal.Dot(dir) < 0) normal = normal * -1.0f;

    return CollisionData(true, normal, minOverlap);
}

CollisionData AABB::IntersectSphere(const BoundingSphere& sphere) const {
    Vector3 c = sphere.GetCenter();

    // Closest point on AABB to sphere center
    Vector3 closest(
        std::clamp(c.x, min.x, max.x),
        std::clamp(c.y, min.y, max.y),
        std::clamp(c.z, min.z, max.z)
    );

    // Vector from closest point on AABB to sphere center
    Vector3 delta = c - closest;
    float distSq = delta.LengthSquared();
    float r = sphere.GetRadius();

    if (distSq >= r * r) return CollisionData(false);

    float dist = std::sqrt(distSq);
    Vector3 normal = (dist > 0.0001f) ? delta * (1.0f / dist) : Vector3(0,1,0);
    return CollisionData(true, normal, r - dist);
}

CollisionData AABB::IntersectPlane(const Plane& plane) const {
  Vector3 halfExtents = GetHalfExtents();
  Vector3 n = plane.GetNormal();

  // Effective radius of AABB projected onto plane normal
  float projectedRadius = std::abs(n.x * halfExtents.x)
                        + std::abs(n.y * halfExtents.y)
                        + std::abs(n.z * halfExtents.z);

  Vector3 center = GetCenter();
  float centerDist = n.Dot(center) - plane.GetDistance();
  float penetration = projectedRadius - std::abs(centerDist);

  if (penetration <= 0.0f) return CollisionData(false);

  // Normal points from AABB center to plane
  Vector3 normal = (centerDist >= 0) ? n * -1.0f : n;
  return CollisionData(true, normal, penetration);
}