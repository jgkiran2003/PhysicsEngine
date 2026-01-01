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

        // Reflect velocity for object i
        float dotI = objects[i]->GetVelocity().Dot(normal);
        if (dotI < 0) { // Only bounce if moving TOWARD the hit
          objects[i]->SetVelocity(objects[i]->GetVelocity() - (normal * 2.0f * dotI));
        }

        // Reflect velocity for object j
        float dotJ = objects[j]->GetVelocity().Dot(normal);
        if (dotJ > 0) { // Only bounce if moving TOWARD the hit
          objects[j]->SetVelocity(objects[j]->GetVelocity() - (normal * 2.0f * dotJ));
        }
      }
    }
  }     
}