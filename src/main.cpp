#include <SDL2/SDL.h>
#include "physics/PhysicsObject.h"
#include "physics/PhysicsEngine.h"
#include "physics/BoundingSphere.h"
#include "physics/Plane.h"
#include "physics/AABB.h"
#include "render/Renderer.h"

int main(int argc, char* argv[]) {
  // Initiliase renderer and physics engine
  Renderer renderer(820, 620);
  PhysicsEngine engine;

  // 4 planes facing inward to form a box
  engine.AddObject(new PhysicsObject(new Plane(Vector3(1, 0, 0), -400), Vector3(0, 0, 0), 0.0f)); // Left Wall
  engine.AddObject(new PhysicsObject(new Plane(Vector3(1, 0, 0), 400), Vector3(0, 0, 0), 0.0f));  // Right Wall
  engine.AddObject(new PhysicsObject(new Plane(Vector3(0, 1, 0), -300), Vector3(0, 0, 0), 0.0f)); // Floor
  engine.AddObject(new PhysicsObject(new Plane(Vector3(0, 1, 0), 300), Vector3(0, 0, 0), 0.0f));  // Ceiling
  engine.AddObject(new PhysicsObject(new Plane(Vector3(0, 0, 1), -400), Vector3(0, 0, 0), 0.0f)); // Back
  engine.AddObject(new PhysicsObject(new Plane(Vector3(0, 0, 1), 400), Vector3(0, 0, 0), 0.0f));  // Front

  // Add two AABB boxes
  engine.AddObject(new PhysicsObject(new AABB(Vector3(-50, -50, -50), Vector3(50, 50, 50)), Vector3(0, 0, 0), 0.0f));
  engine.AddObject(new PhysicsObject(new AABB(Vector3(100, 100, 100), Vector3(150, 150, 150)), Vector3(10.0, 5.0, 0), 1.0f));

  // 50 particles randomly generated within box
  for(int i = 0; i < 50; i++) {
    // Random position between (50, 50) and (750, 550)
    float startX = -350 + (rand() % 700);
    float startY = -250 + (rand() % 500);
    float startZ = -350 + (rand() % 700);

    // Random velocity
    float velX = (rand() % 20) - 10;
    float velY = (rand() % 20) - 10;
    float velZ = (rand() % 20) - 10;

    // Random mass
    // float mass = (rand() % 5) + 5;
    float mass = 1.0f;

    BoundingSphere* particleShape = new BoundingSphere(Vector3(startX, startY, startZ), 5.0f);
    engine.AddObject(new PhysicsObject(particleShape, Vector3(velX, velY, velZ), mass));
  }

  // Main loop
  float timeStep = 0.1f;

  while (renderer.IsOpen()) {
    renderer.HandleEvents();
    
    engine.Simulate(timeStep);

    renderer.Clear();
    renderer.Render3D(engine.objects);
    renderer.Present();
  }

  return 0;
}