#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Vector2.h"
#include "Collider.h"

class PhysicsObject {
  public:
    // Constructor
    PhysicsObject(Collider* collider, const Vector2& vel);

    // Destructor
    ~PhysicsObject();

    // Movement
    void Integrate(float delta);

    // Getters
    inline Vector2 GetPosition() const { return collider->GetCenter(); }
    inline Vector2 GetVelocity() const { return velocity; }
    inline Collider& GetCollider() { return *collider; }

    // Setters
    inline void SetVelocity(const Vector2& vel) { velocity = vel; }
  
  private:
    Vector2 velocity;
    Collider* collider;
};

#endif