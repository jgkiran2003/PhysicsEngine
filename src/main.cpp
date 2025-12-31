#include <iostream>
#include <SDL2/SDL.h>
#include "PhysicsObject.h"

int main(int argc, char* argv[]) {
  // Setup SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Physics Visualizer", 100, 100, 800, 600, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Setup Physics
  Vector2 startPos(0.0f, 0.0f);
  Vector2 startVel(10.0f, 10.0f);
  PhysicsObject ball(startPos, startVel);
  float timeStep = 1.0f;

  bool running = true;
  SDL_Event event;

  while (running) {
    // Handle closing the window
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
    }

    // --- CORE LOGIC ---
    ball.integrate(timeStep);

    // Clear the screen to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    SDL_Rect rect = { (int)ball.position.x, (int)ball.position.y, 10, 10 };
    SDL_RenderFillRect(renderer, &rect);
  
    // Show the result
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // Run at ~60 frames per second
  }

  SDL_Quit();
  return 0;
}