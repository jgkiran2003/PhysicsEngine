#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include "PhysicsObject.h"

class PhysicsEngine {
public:
  // List of every object in the world
  std::vector<PhysicsObject*> objects;

  // Adds a new object to the environment
  void AddObject(PhysicsObject* object);

  void Simulate(float delta);

  // Helper to get specific objects
  PhysicsObject* GetObject(unsigned int index) { return objects[index]; }
  unsigned int GetNumObjects() { return objects.size(); }
};

#endif