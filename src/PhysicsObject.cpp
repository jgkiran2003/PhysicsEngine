#include "PhysicsObject.h"

// Constructor
PhysicsObject::PhysicsObject(Vector2 pos, Vector2 vel) : 
  position(pos), 
  velocity(vel) 
{
  // Body is empty because we initialized above
}

// Movement
void PhysicsObject::integrate(float deltaTime) {
  position = position + velocity * deltaTime;
}