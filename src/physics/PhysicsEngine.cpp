#include "PhysicsEngine.h"

void PhysicsEngine::AddObject(PhysicsObject* object) {
  objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta) {
  // CONSTANT FORCES (Global)
  Vector3 gravity(0.0f, -1.0f, 0.0f);

  // Add global forces
  for (auto* obj : objects) {
    if (obj->GetInvMass() > 0.0f) {
      Vector3 gravityForce = gravity / obj->GetInvMass();
      obj->AddForce(gravityForce);
    }
  }
  
  // Move everything
  for (int i = 0; i < objects.size(); i++) {
    objects[i]->Integrate(delta);
  }

  // Check for collisions
  for (int i = 0; i < objects.size(); i++) {
    for (int j = i + 1; j < objects.size(); j++) {
      CollisionData collisionData = 
        objects[i]->GetCollider().Intersect(objects[j]->GetCollider());

      // Resolve collision
      if (collisionData.DoesInteract()) {
        // Positional correction
        objects[i]->GetCollider().Transform(collisionData.GetDirection() * -collisionData.GetDistance());
        objects[j]->GetCollider().Transform(collisionData.GetDirection() * collisionData.GetDistance());

        // Direction of normal force acting on object j
        Vector3 normal = collisionData.GetDirection().Normalized();
        Vector3 relativeVelocity = objects[i]->GetVelocity() - objects[j]->GetVelocity();
        float normalVelocity = relativeVelocity.Dot(normal);
        // Do not resolve if moving apart
        if (normalVelocity < 0) continue;

        float invMassSum = objects[i]->GetInvMass() + objects[j]->GetInvMass();
        if (invMassSum > 0.0f) {
          float e = 1.0f; 
          float k = -(1.0f + e) * normalVelocity / invMassSum;
          Vector3 impulse = normal * k;

          objects[i]->SetVelocity(objects[i]->GetVelocity() + (impulse * objects[i]->GetInvMass()));
          objects[j]->SetVelocity(objects[j]->GetVelocity() - (impulse * objects[j]->GetInvMass()));
        }
      }
    }
  }     
}