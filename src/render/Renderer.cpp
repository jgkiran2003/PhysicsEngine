#include "Renderer.h"
#include "physics/PhysicsObject.h"
#include "physics/BoundingSphere.h"
#include "physics/Plane.h"

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
  for (auto* obj : objects) {
    Collider& col = obj->GetCollider();
  
    // Only draw if it's actually a sphere
    if (col.GetType() == Collider::TYPE_SPHERE) {
      SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255); // White balls
      Vector2 pos = obj->GetPosition();
      BoundingSphere& sphere = (BoundingSphere&)col;
      DrawCircle((int)pos.x, (int)pos.y, (int)sphere.GetRadius());
    } 
    else if (col.GetType() == Collider::TYPE_PLANE) {
      SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255); // Red for planes
      Plane& plane = (Plane&)col;
      Vector2 normal = plane.GetNormal();
      float dist = plane.GetDistance();

      // 1. Closest point on plane to origin
      Vector2 originPoint = normal * dist;

      // 2. Find the "surface direction" (rotate normal by 90 degrees)
      Vector2 surfaceDir = Vector2(normal.y, -normal.x);

      // 3. Draw a long line along that surface direction
      Vector2 p1 = originPoint + (surfaceDir * 2000); // 2000 is long enough to cover screen
      Vector2 p2 = originPoint - (surfaceDir * 2000);

      DrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
    }
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

void Renderer::DrawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}