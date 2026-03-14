#include "PhysicsObject.h"

// Destructor
PhysicsObject::~PhysicsObject() {
  if (collider) {
    delete collider; // Manually free the memory allocated with 'new'
  }
}
// Movement
void PhysicsObject::Integrate(float delta, const Vector3& globalAcceleration=Vector3(0, 0, 0)) {
  if (inverseMass <= 0.0f) return;

  Vector3 acceleration = forceAccumulator * inverseMass;  // Newton's Second Law
  Vector3 totalAcceleration = acceleration + globalAcceleration; // Add globals (gravity)
  velocity = velocity + totalAcceleration * delta;
  Vector3 displacement = velocity * delta;
  collider->Transform(displacement);
  
  ClearForceAccumulator();
}