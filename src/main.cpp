#include <SDL2/SDL.h>
#include "physics/PhysicsObject.h"
#include "physics/PhysicsEngine.h"
#include "physics/BoundingSphere.h"
#include "physics/Plane.h"
#include "render/Renderer.h"

int main(int argc, char* argv[]) {
  // Initiliase renderer and physics engine
  Renderer renderer(820, 620);
  PhysicsEngine engine;

  // 4 planes facing inward to form a box
  engine.AddObject(new PhysicsObject(new Plane(Vector2(1, 0), -400), Vector2(0, 0))); // Left Wall
  engine.AddObject(new PhysicsObject(new Plane(Vector2(1, 0), 400), Vector2(0, 0)));  // Right Wall
  engine.AddObject(new PhysicsObject(new Plane(Vector2(0, 1), -300), Vector2(0, 0))); // Ceiling
  engine.AddObject(new PhysicsObject(new Plane(Vector2(0, 1), 300), Vector2(0, 0)));  // Floor

  // 50 particles randomly generated within box
  for(int i = 0; i < 50; i++) {
    // Random position between (50, 50) and (750, 550)
    float startX = -350 + (rand() % 700);
    float startY = -250 + (rand() % 500);

    // Random velocity
    float velX = (rand() % 10) - 5;
    float velY = (rand() % 10) - 5;

    BoundingSphere* particleShape = new BoundingSphere(Vector2(startX, startY), 4.0f);
    engine.AddObject(new PhysicsObject(particleShape, Vector2(velX, velY)));
  }

  // Main loop
  float timeStep = 0.1f;

  while (renderer.IsOpen()) {
    renderer.HandleEvents();
    
    engine.Simulate(timeStep);

    renderer.Clear();
    renderer.Render(engine.objects);
    renderer.Present();
  }

  return 0;
}