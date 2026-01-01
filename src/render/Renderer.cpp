#include "Renderer.h"
#include "physics/PhysicsObject.h"
#include "physics/BoundingSphere.h"

Renderer::Renderer(int width, int height) : isOpen(true) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Renderer::Clear() {
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); // Black background
  SDL_RenderClear(sdlRenderer);
}

void Renderer::Render(const std::vector<PhysicsObject*>& objects) {
  SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255); // White objects

  for (auto* obj : objects) {
    // Only BoundingSphere for now
    Vector2 pos = obj->GetPosition();
    
    BoundingSphere& sphere = (BoundingSphere&)obj->GetCollider();
    DrawCircle((int)pos.x, (int)pos.y, (int)sphere.GetRadius());
  }
}

void Renderer::Present() {
  SDL_RenderPresent(sdlRenderer);
}

void Renderer::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) isOpen = false;
  }
}

// Simple midpoint circle algorithm
void Renderer::DrawCircle(int centerX, int centerY, int radius) {
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; 
      int dy = radius - h;
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(sdlRenderer, centerX + dx, centerY + dy);
      }
    }
  }
}