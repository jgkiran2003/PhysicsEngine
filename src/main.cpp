#include <SDL2/SDL.h>
#include "PhysicsObject.h"
#include "PhysicsEngine.h"

int main(int argc, char* argv[]) {
  // Setup SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Physics Visualizer", 100, 100, 800, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Setup Physics Engine
  PhysicsEngine engine;
  
  float timeStep = 1.0f;

  // Create a ball
  PhysicsObject* ball = new PhysicsObject(Vector2(200, 100), Vector2(0.1, 0));
  engine.AddObject(ball);

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

    // Draw the ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    Vector2 ballPosition = ball->GetPosition();
    SDL_Rect rect = { (int)ballPosition.x, (int)ballPosition.y, 10, 10 };
    SDL_RenderFillRect(renderer, &rect);
  
    // Show the result
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // Run at ~60 frames per second
  }

  SDL_Quit();
  return 0;
}