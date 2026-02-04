# 3D Physics Engine

This project is a custom-built 3D physics engine written from scratch in C++. It features a robust physics simulation loop, handling of various collision shapes, and a real-time 3D visualization.

This engine was built to demonstrate a deep understanding of physics simulation principles, object-oriented design in C++, and the mathematics of 3D graphics.

**Project Goal**: This engine was developed as a first-principles exploration of rigid-body dynamics and high-performance C++. The objective was to implement core simulation patterns without the abstraction of existing game engines.

## Key Features

-   **Real-time 3D Simulation:** Visualizes the physics simulation in real-time using SDL and OpenGL.
-   **Rigid Body Dynamics:** Implements a complete physics simulation loop including force accumulation, semi-implicit Euler integration, and impulse-based collision response.
-   **Polymorphic Collision System:** Supports multiple collision shapes (Spheres, Planes) through a polymorphic architecture.
-   **Stable Collision Response:** Includes both impulse-based velocity changes and positional correction to prevent objects from sinking into each other.
-   **Clean, Modular Architecture:** A clear separation between the physics simulation and rendering logic.
-   **CMake Build System:** A clean and modern build system for easy compilation on Linux.

## Core Architecture

The engine is designed with a strong emphasis on modularity and Object-Oriented principles.

**`PhysicsEngine`**: The central orchestrator. It manages all physics objects and executes the main simulation loop.

**`PhysicsObject`**: Represents any object with physical properties. It *has a* `Collider` to define its shape and handles its own movement through integration.

**`Collider` (Abstract Base Class)**: Defines the interface for any collision shape. This polymorphic design allows the engine to be easily extended with new shapes (e.g., AABB, Capsules).

**`BoundingSphere` & `Plane`**: Concrete implementations of the `Collider` interface.

**`Renderer`**: A standalone class that encapsulates all SDL and OpenGL rendering logic, completely decoupled from the physics simulation.

## Technical Deep Dive

This project solves several complex technical challenges with robust and elegant solutions.

### 1. Polymorphic Collision Detection via Double Dispatch

A key challenge in a physics engine is determining which collision detection algorithm to use for any two given shapes. This engine solves this using a form of **double dispatch**.

-   The base `Collider` class has an `Intersect(const Collider& other)` method.
-   This method checks the types of both `this` collider and the `other` collider.
-   It then casts the colliders to their concrete types (`BoundingSphere*`, `Plane*`) and calls the appropriate specialized intersection function (e.g., `IntersectSphere`).

This approach is highly extensible, allowing new collision shape combinations to be added by simply extending the logic in this central dispatch function.

### 2. The Physics Simulation Loop

The `PhysicsEngine::Simulate` method implements an ordered simulation loop, which is critical for stability and realism.

```
For each frame:
  1. Apply Global Forces (e.g., Gravity)
  2. Integrate Motion (Update position and velocity for each object)
  3. Detect Collisions (The N-body problem)
  4. Resolve Collisions (Impulse and Positional Correction)
```

This project implements **Semi-implicit Euler integration** in the `PhysicsObject::Integrate` method. This method is favored in game physics for its stability and computational efficiency compared to explicit Euler.

### 3. Impulse-Based Collision Response

When objects collide, their velocities must be updated realistically. This engine uses a standard and correct **impulse-based model** to resolve collisions.

The key formula, implemented in `PhysicsEngine::Simulate`, calculates the scalar magnitude of the impulse (`k`) to be applied along the collision normal:

`k = -(1.0f + e) * normalVelocity / invMassSum;`

Where:
-   `e` is the coefficient of restitution (bounciness).
-   `normalVelocity` is the relative velocity of the objects along the collision normal.
-   `invMassSum` is the sum of the inverse masses of the two objects.

This correctly models the conservation of momentum and energy in a collision.

### 4. Positional Correction for Stability

A common problem in physics engines is "sinking," where objects slowly penetrate each other over time due to precision errors. This engine solves this with **positional correction**.

When a collision is detected, the penetration distance is calculated. The objects are then immediately pushed apart by this distance, ensuring they rest on top of each other correctly. This is a crucial feature for creating a stable and visually convincing simulation.

## How to Build and Run

The project uses CMake for building.

**Prerequisites:**
-   A C++ compiler (g++)
-   CMake
-   SDL2, GLEW, and OpenGL development libraries.

    ```bash
    sudo apt-get install build-essential cmake libsdl2-dev libglew-dev libglu1-mesa-dev
    ```

**Building:**
1.  Clone the repository.
2.  Create a build directory: `mkdir build && cd build`
3.  Run CMake: `cmake ..`
4.  Compile: `make`
5.  Run the executable: `./engine`

## Future Improvements

-   **Modernize Renderer:** Replace the legacy OpenGL fixed-function pipeline with a modern, shader-based pipeline (OpenGL 3.3+).
-   **More Collision Shapes:** Implement more complex collision shapes like Axis-Aligned Bounding Boxes (AABB) and Capsules.
-   **Broadphase Optimization:** Implement a spatial partitioning structure (like a grid or octree) to optimize collision detection and avoid the O(n^2) check between all objects.
-   **Rotational Dynamics:** Extend the physics objects to handle torque, angular velocity, and orientation for more complex simulations.
