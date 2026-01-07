#include "PhysicsObject.h"

// Destructor
PhysicsObject::~PhysicsObject() {
  if (collider) {
    delete collider; // Manually free the memory allocated with 'new'
  }
}
// Movement
void PhysicsObject::Integrate(float delta) {
  if (inverseMass <= 0.0f) return;

  Vector3 acceleration = forceAccumulator * inverseMass;  // Newton's Second Law
  velocity = velocity + acceleration * delta;
  Vector3 displacement = velocity * delta;
  collider->Transform(displacement);
  
  ClearForceAccumulator();
}