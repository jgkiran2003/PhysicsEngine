#include "Renderer.h"
#include "physics/PhysicsObject.h"
#include "physics/BoundingSphere.h"
#include "physics/Plane.h"
#include "physics/Vector3.h"

#include <GL/glew.h>         // Must be first
#include <GL/glu.h>          // OpenGL Utility Library
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
  rotationY = 0.0f;
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
  // Setup the "Projection" (The Lens)
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // This creates a 75-degree field of view with a near and far clipping plane
  gluPerspective(75.0, 820.0/620.0, 1.0, 2000.0);

  // Reset the "View" so rotations don't stack every frame
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Move the camera back 1000 units so we can see the center (0,0,0)
  glTranslatef(0, 0, -1000.0f);

  // Apply the rotation around the Y axis (0, 1, 0)
  glRotatef(rotationY, 0, 1, 0);
  
  // Simple projection without shaders
  for (auto* obj : objects) {
    Collider& col = obj->GetCollider();
    Vector3 pos = obj->GetPosition() + camera_offset;

    if (col.GetType() == Collider::TYPE_SPHERE) {
      float r = ((BoundingSphere&)col).GetRadius();
      DrawSimplePoint(pos, r);
    }
  }

  DrawBoxSimple(); 
}

void Renderer::Present() {
  SDL_GL_SwapWindow(window);
}

void Renderer::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) isOpen = false;
    // Check for key presses
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          rotationY -= 2.0f; // Spin left
          break;
        case SDLK_RIGHT:
          rotationY += 2.0f; // Spin right
          break;
      }
    }
  }
}

void Renderer::DrawSimplePoint(const Vector3& pos, float size) {
    glPointSize(size); // Set size BEFORE glBegin
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(pos.x, pos.y, pos.z); 
    glEnd();
}

void Renderer::DrawBoxSimple() {
    // Boundaries from your main.cpp planes
    float x = 400.0f;
    float y = 300.0f;
    float z = 400.0f;

    // --- Transparent Faces ---
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE); // Particles inside will be visible through the walls
    glColor4f(0.2f, 0.4f, 1.0f, 0.1f); // Very faint blue

    glBegin(GL_QUADS);
      // Front (Z = -400)
      glVertex3f(-x, -y, -z); glVertex3f( x, -y, -z); 
      glVertex3f( x,  y, -z); glVertex3f(-x,  y, -z);
      // Back (Z = 400)
      glVertex3f(-x, -y,  z); glVertex3f( x, -y,  z); 
      glVertex3f( x,  y,  z); glVertex3f(-x,  y,  z);
      // Left (X = -400)
      glVertex3f(-x, -y, -z); glVertex3f(-x, -y,  z); 
      glVertex3f(-x,  y,  z); glVertex3f(-x,  y, -z);
      // Right (X = 400)
      glVertex3f( x, -y, -z); glVertex3f( x, -y,  z); 
      glVertex3f( x,  y,  z); glVertex3f( x,  y, -z);
      // Top (Y = -300)
      glVertex3f(-x, -y, -z); glVertex3f( x, -y, -z); 
      glVertex3f( x, -y,  z); glVertex3f(-x, -y,  z);
      // Bottom (Y = 300)
      glVertex3f(-x,  y, -z); glVertex3f( x,  y, -z); 
      glVertex3f( x,  y,  z); glVertex3f(-x,  y,  z);
    glEnd();

    // --- Solid Wireframe Outlines ---
    glDepthMask(GL_TRUE); // Turn depth writing back on
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Semi-transparent white

    // Re-draw the same geometry as lines
    glBegin(GL_QUADS);
      glVertex3f(-x, -y, -z); glVertex3f( x, -y, -z); glVertex3f( x,  y, -z); glVertex3f(-x,  y, -z);
      glVertex3f(-x, -y,  z); glVertex3f( x, -y,  z); glVertex3f( x,  y,  z); glVertex3f(-x,  y,  z);
      glVertex3f(-x, -y, -z); glVertex3f(-x, -y,  z); glVertex3f(-x,  y,  z); glVertex3f(-x,  y, -z);
      glVertex3f( x, -y, -z); glVertex3f( x, -y,  z); glVertex3f( x,  y,  z); glVertex3f( x,  y, -z);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to standard filling
}