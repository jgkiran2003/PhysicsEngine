#ifndef INTERSECT_DATA_H
#define INTERSECT_DATA_H

#include "Vector2.h"

class IntersectData {
  public:
    IntersectData(const bool doesInteract, const Vector2& direction) : 
      doesInteract(doesInteract), 
      direction(direction) {}

    inline bool DoesInteract() const { return doesInteract; }
    inline Vector2 GetDirection() const { return direction; }

  private:
    const bool doesInteract;
    // Direction of penetration - normal vector of collision
    // Normal vector from closest point on this objects surface to other objects center
    const Vector2 direction;
};

#endif