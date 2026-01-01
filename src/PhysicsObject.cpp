#include "PhysicsObject.h"

// Constructor
PhysicsObject::PhysicsObject(Vector2 pos, Vector2 vel) : 
  position(pos), 
  velocity(vel) {}

// Movement
void PhysicsObject::Integrate(float delta) {
  position = position + velocity * delta;
}