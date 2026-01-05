#ifndef COLLIDER_H
#define COLLIDER_H

#include "IntersectData.h"
#include "Vector3.h"

class Collider {
  public:
    enum {
      TYPE_SPHERE,
      TYPE_AABB,
      TYPE_PLANE,
      
      TYPE_SIZE
    };

    // Constructor
    Collider(int type) : type(type) {}

    // Checks for collisions
    IntersectData Intersect(const Collider& other) const;

    // Virtual to be overriden
    virtual void Transform(const Vector3& translation) {}
    virtual Vector3 GetCenter() const { return Vector3(0, 0, 0); }

    inline int GetType() const { return type; }

  private:
    int type;
};

#endif