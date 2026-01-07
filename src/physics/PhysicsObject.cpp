#include "PhysicsObject.h"

// Destructor
PhysicsObject::~PhysicsObject() {
  if (collider) {
    delete collider; // Manually free the memory allocated with 'new'
  }
}
// Movement
void PhysicsObject::Integrate(float delta) {
  Vector3 displacement = velocity * delta;
  collider->Transform(displacement);
}