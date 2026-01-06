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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

  glDepthMask(GL_FALSE); 
  DrawBox(); 
  glDepthMask(GL_TRUE);
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

void Renderer::DrawBox() {
    glBegin(GL_QUADS);
    
    // Set a transparent blue color (RGBA)
    glColor4f(0.2f, 0.4f, 1.0f, 0.2f);

    // Define the boundaries based on your main.cpp planes
    float x = 400.0f;
    float y = 300.0f;
    float z = 400.0f;

    // We apply the same perspective/camera logic as the particles
    auto project = [&](float px, float py, float pz) {
        float z_final = (pz + camera_offset.z) + 1000.0f;
        float x_proj = (px * 500.0f) / z_final;
        float y_proj = (py * 500.0f) / z_final;
        glVertex3f(x_proj / 400.0f, y_proj / 300.0f, 0.0f);
    };

    // Back Face (Z = 400)
    project(-x, -y, z); project(x, -y, z); project(x, y, z); project(-x, y, z);
    // Front Face (Z = -400)
    project(-x, -y, -z); project(x, -y, -z); project(x, y, -z); project(-x, y, -z);
    // Left Face (X = -400)
    project(-x, -y, -z); project(-x, -y, z); project(-x, y, z); project(-x, y, -z);
    // Right Face (X = 400)
    project(x, -y, -z); project(x, -y, z); project(x, y, z); project(x, y, -z);
    // Floor (Y = 300)
    project(-x, y, -z); project(x, y, -z); project(x, y, z); project(-x, y, z);
    // Ceiling (Y = -300)
    project(-x, -y, -z); project(x, -y, -z); project(x, -y, z); project(-x, -y, z);

    glEnd();

    // Optional: Draw wireframe edges so the box is easier to see
    glLineWidth(2.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // White outlines
    // Repeat the project calls here...
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to fill
}