#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H

#include "Vector3.h"

class CollisionData {
  public:
    CollisionData(
      const bool doesInteract, 
      const Vector3& direction = Vector3(0, 0), 
      const float distance = 0.0f
    ) : 
      doesInteract(doesInteract), 
      direction(direction),
      distance(distance) {}

    inline bool DoesInteract() const { return doesInteract; }
    inline Vector3 GetDirection() const { return direction; }
    inline float GetDistance() const { return distance; }

  private:
    const bool doesInteract;
    // Direction of penetration - normal vector of collision
    // Normal vector from closest point on this objects surface to other objects center
    // CONVENTION: 
    //    Direction is the normal pointing FROM object A (the caller)
    //    TO object B (the argument). Positional correction pushes
    //    A backward and B forward along this normal.
    const Vector3 direction;
    float distance;
};

#endif