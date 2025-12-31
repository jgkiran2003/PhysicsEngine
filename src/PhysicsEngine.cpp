#include "PhysicsEngine.h"

void PhysicsEngine::AddObject(PhysicsObject* object) {
  objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta) {
  for (int i = 0; i < objects.size(); i++) {
    objects[i]->Integrate(delta);
  }
}