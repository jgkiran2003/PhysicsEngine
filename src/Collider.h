#ifndef COLLIDER_H
#define COLLIDER_H

#include "IntersectData.h"
#include "Vector2.h"
#include "PhysicsObject.h"

class Collider {
  public:
    enum {
      TYPE_CIRCLE,
      TYPE_AABB,
      
      TYPE_SIZE
    };

    // Constructor
    Collider(int type) : type(type) {}

    // Checks for collisions
    IntersectData Intersect(const Collider& other) const;

    // Virtual to be overriden
    virtual void Transform(const Vector2& translation) {}
    virtual Vector2 GetCenter() const { return Vector2(0, 0); }

    inline int GetType() const { return type; }

  private:
    int type;
};

#endif