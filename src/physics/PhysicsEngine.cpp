#include "PhysicsEngine.h"

void PhysicsEngine::AddObject(PhysicsObject* object) {
  objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta) {
  // Move everything
  for (int i = 0; i < objects.size(); i++) {
    objects[i]->Integrate(delta);
  }

  // Check for collisions
  for (int i = 0; i < objects.size(); i++) {
    for (int j = i + 1; j < objects.size(); j++) {
      IntersectData intersectData = 
        objects[i]->GetCollider().Intersect(objects[j]->GetCollider());

      // Resolve collision
      if (intersectData.DoesInteract()) {
        // Direction of normal force acting on object j
        Vector2 normal = intersectData.GetDirection().Normalized();

        Vector2 relativeVelocity = objects[i]->GetVelocity() - objects[j]->GetVelocity();
        float normalVelocity = relativeVelocity.Dot(normal);
        // Do not resolve if moving apart
        if (normalVelocity < 0) continue;

        float massSum = objects[i]->GetInvMass() + objects[j]->GetInvMass();
        if (massSum > 0.0f) {
          float e = 1.0f; 
          float j_scalar = -(1.0f + e) * normalVelocity;
          j_scalar /= massSum;

          Vector2 impulseVec = normal * j_scalar;

          // Object A gets pushed (using your A->B normal convention)
          objects[i]->SetVelocity(objects[i]->GetVelocity() + (impulseVec * objects[i]->GetInvMass()));
          
          // Object B gets pushed opposite
          objects[j]->SetVelocity(objects[j]->GetVelocity() - (impulseVec * objects[j]->GetInvMass()));
        }
      }
    }
  }     
}