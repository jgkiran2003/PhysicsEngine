#include <SDL2/SDL.h>
#include "physics/PhysicsObject.h"
#include "physics/PhysicsEngine.h"
#include "physics/BoundingSphere.h"
#include "render/Renderer.h"

int main(int argc, char* argv[]) {
  // Initiliase renderer and physics engine
  Renderer renderer(800, 600);
  PhysicsEngine engine;

  // Add balls
  engine.AddObject(new PhysicsObject(new BoundingSphere(Vector2(100, 300), 20), Vector2(2, 0)));
  engine.AddObject(new PhysicsObject(new BoundingSphere(Vector2(700, 300), 20), Vector2(-2, 0)));

  // Main loop
  float timeStep = 1.0f;

  while (renderer.IsOpen()) {
    renderer.HandleEvents();
    
    engine.Simulate(timeStep);

    renderer.Clear();
    renderer.Render(engine.objects);
    renderer.Present();
  }

  return 0;
}