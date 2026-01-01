#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>

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

private:
    SDL_Window*   window;
    SDL_Renderer* sdlRenderer;
    bool          isOpen;

    // Set origin coordinates to center of window
    float origin_x;
    float origin_y;

    // Helper to draw a circle
    void DrawCircle(int centerX, int centerY, int radius);

    // Helper to draw a line
    void DrawLine(int x1, int y1, int x2, int y2);
};

#endif