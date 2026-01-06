#include "Renderer.h"
#include "physics/PhysicsObject.h"
#include "physics/BoundingSphere.h"
#include "physics/Plane.h"
#include "physics/Vector3.h"

#include <GL/glew.h>         // Must be first
#include <SDL2/SDL.h>        // Standard SDL
#include <SDL2/SDL_opengl.h> // SDL's OpenGL support

Renderer::Renderer(int width, int height) : isOpen(true) {
  SDL_Init(SDL_INIT_VIDEO);
  
  // 1. Request an OpenGL context (3.3 Core is standard)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  // 2. Create window with OPENGL flag
  window = SDL_CreateWindow("3D Physics Engine", SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

  // 3. Create the OpenGL Context (replaces SDL_CreateRenderer)
  glContext = SDL_GL_CreateContext(window);

  // 4. Init GLEW to load OpenGL functions
  glewExperimental = GL_TRUE;
  glewInit();

  // 5. Enable Depth Testing (so balls don't overlap wrongly)
  glEnable(GL_DEPTH_TEST);

  camera_offset = Vector3(0, 0, 0);

  // window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_UNDEFINED, 
  //                             SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  // sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
  // SDL_DestroyRenderer(sdlRenderer);
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Renderer::Clear() {
  // SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); // Black background
  // SDL_RenderClear(sdlRenderer);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth
}

void Renderer::Render2D(const std::vector<PhysicsObject*>& objects) {
  for (auto* obj : objects) {
    Collider& col = obj->GetCollider();
  
    // Only draw if it's actually a sphere
    if (col.GetType() == Collider::TYPE_SPHERE) {
      SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255); // White balls
      Vector3 pos = obj->GetPosition() + camera_offset;
      BoundingSphere& sphere = (BoundingSphere&)col;
      DrawCircle((int)pos.x, (int)pos.y, (int)sphere.GetRadius());
    } 
    else if (col.GetType() == Collider::TYPE_PLANE) {
      SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255); // Red for planes
      Plane& plane = (Plane&)col;
      Vector3 normal = plane.GetNormal();
      float dist = plane.GetDistance();

      // 1. Closest point on plane to origin
      Vector3 originPoint = normal * dist;

      // 2. Find the "surface direction" (rotate normal by 90 degrees)
      Vector3 surfaceDir = Vector3(normal.y, -normal.x);

      // 3. Draw a long line along that surface direction
      Vector3 p1 = originPoint + (surfaceDir * 2000) + camera_offset;
      Vector3 p2 = originPoint - (surfaceDir * 2000) + camera_offset;

      DrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
    }
  }
}

void Renderer::Render3D(const std::vector<PhysicsObject*>& objects) {
  // Simple projection without shaders
  for (auto* obj : objects) {
    Collider& col = obj->GetCollider();
    Vector3 pos = obj->GetPosition() + camera_offset;

    if (col.GetType() == Collider::TYPE_SPHERE) {
      float r = ((BoundingSphere&)col).GetRadius();
      
      DrawPoint3D(pos, r);
    }
  }
}

void Renderer::Present() {
  // SDL_RenderPresent(sdlRenderer);
  SDL_GL_SwapWindow(window);
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

void Renderer::DrawPoint3D(const Vector3& pos, float size) {
  float z_final = pos.z + 1000.0f;
  float x_proj = (pos.x * 500.0f) / z_final;
  float y_proj = (pos.y * 500.0f) / z_final;
  glPointSize(size * (1000.0f / z_final));

  // Legacy 3D visualisation
  glBegin(GL_POINTS);
  glColor3f(1.0f, 1.0f, 1.0f); // White

  glVertex3f(x_proj / 400.0f, y_proj / 300.0f, 0.0f); 
  glEnd();
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}