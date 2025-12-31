#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Vector2.h"

class PhysicsObject {
  public:
    Vector2 position;
    Vector2 velocity;

    PhysicsObject(Vector2 pos, Vector2 vel) : position(pos), velocity(vel) {}

    void integrate(float deltaTime) {
      position = position + velocity * deltaTime;
    }

};

#endif