#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include "physics/Vector3.h"

class PhysicsObject; // Forward declaration

class Renderer {
public:
    // Constructor and destructor
    Renderer(int width, int height);
    ~Renderer();

    // Functions
    void Clear();
    void Render(const std::vector<PhysicsObject*>& objects);
    void Present();

    bool IsOpen() const { return isOpen; }
    void HandleEvents();

    void setOrigin(float x, float y, float z) {camera_offset = Vector3(x, y, z); }

private:
    SDL_Window*   window;
    SDL_Renderer* sdlRenderer;
    bool          isOpen;

    // Set origin coordinates to center of window
    Vector3 camera_offset;

    // Helper to draw a circle
    void DrawCircle(int centerX, int centerY, int radius);

    // Helper to draw a line
    void DrawLine(int x1, int y1, int x2, int y2);
};

#endif