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
  
  // Request an OpenGL context (3.3 Core is standard)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  
  // Create window with OPENGL flag
  window = SDL_CreateWindow("3D Physics Engine", SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

  // Create the OpenGL Context (replaces SDL_CreateRenderer)
  glContext = SDL_GL_CreateContext(window);

  // Init GLEW to load OpenGL functions
  glewExperimental = GL_TRUE;
  glewInit();

  // Enable Depth Testing (so balls don't overlap wrongly)
  glEnable(GL_DEPTH_TEST);

  camera_offset = Vector3(0, 0, 0);
}

Renderer::~Renderer() {
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Renderer::Clear() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth
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
  SDL_GL_SwapWindow(window);
}

void Renderer::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) isOpen = false;
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