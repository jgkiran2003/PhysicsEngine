#include <SDL2/SDL.h>
#include "PhysicsObject.h"
#include "PhysicsEngine.h"
#include "BoundingSphere.h"

int main(int argc, char* argv[]) {
  // Setup SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Physics Visualizer", 100, 100, 800, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Setup Physics Engine
  PhysicsEngine engine;

  // Ball 1
  BoundingSphere* sphere1 = new BoundingSphere(Vector2(100, 100), 10);
  PhysicsObject* ball1 = new PhysicsObject(sphere1, Vector2(3, 0));
  engine.AddObject(ball1);

  // Ball 2
  BoundingSphere* sphere2 = new BoundingSphere(Vector2(800, 100), 10);
  PhysicsObject* ball2 = new PhysicsObject(sphere2, Vector2(-3, 0));
  engine.AddObject(ball2);

  // Main loop
  float timeStep = 1.0f;
  bool running = true;
  SDL_Event event;

  while (running) {
    // Handle closing the window
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
    }

    // Update physics
    engine.Simulate(timeStep);

    // Clear the screen to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw ball 1
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    Vector2 ball1Position = ball1->GetPosition();
    SDL_Rect rect1 = { (int)ball1Position.x, (int)ball1Position.y, 10, 10 };
    SDL_RenderFillRect(renderer, &rect1);

    // Draw ball 2
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    Vector2 ball2Position = ball2->GetPosition();
    SDL_Rect rect2 = { (int)ball2Position.x, (int)ball2Position.y, 10, 10 };
    SDL_RenderFillRect(renderer, &rect2);
  
    // Show the result
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // Run at ~60 frames per second
  }

  SDL_Quit();
  return 0;
}