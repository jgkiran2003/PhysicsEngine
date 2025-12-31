#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Vector2.h"

class PhysicsObject {
  public:
    Vector2 position;
    Vector2 velocity;

    // Constructor
    PhysicsObject(Vector2 pos, Vector2 vel);

    // Movement
    void Integrate(float delta);

    // Getters
    Vector2 GetPosition() const { return position; }
    Vector2 GetVelocity() const { return velocity; }

    // Setters
    void SetPosition(Vector2 pos) { position = pos; }
    void SetVelocity(Vector2 vel) { velocity = vel; }
};

#endif