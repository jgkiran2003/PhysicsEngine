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
        // Perfectly elastic collision of equal masses
        Vector2 v1_temp = objects[i]->GetVelocity();
        objects[i]->SetVelocity(objects[j]->GetVelocity());
        objects[j]->SetVelocity(v1_temp);
      }
    }
  }     
}