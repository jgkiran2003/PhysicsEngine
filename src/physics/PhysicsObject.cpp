#include "PhysicsObject.h"

// Constructor
PhysicsObject::PhysicsObject(Collider* collider, const Vector2& vel) : 
  collider(collider), 
  velocity(vel) {}

// Destructor
PhysicsObject::~PhysicsObject() {
  if (collider) {
    delete collider; // Manually free the memory allocated with 'new'
  }
}
// Movement
void PhysicsObject::Integrate(float delta) {
  Vector2 displacement = velocity * delta;
  collider->Transform(displacement);
}