#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Vector2.h"
#include "Collider.h"

class PhysicsObject {
  public:
    // Constructor
    PhysicsObject(Collider* collider, const Vector2& vel = Vector2(0, 0), const float mass = 1.0f) :
      collider(collider),
      velocity(vel),
      inverseMass(1.0f / mass) {}

    // Destructor
    ~PhysicsObject();

    // Movement
    void Integrate(float delta);

    // Getters
    inline Vector2 GetPosition() const { return collider->GetCenter(); }
    inline Vector2 GetVelocity() const { return velocity; }
    inline Collider& GetCollider() { return *collider; }
    inline float GetInvMass() const { return inverseMass; }

    // Setters
    inline void SetVelocity(const Vector2& vel) { velocity = vel; }
  
  private:
    Vector2 velocity;
    Collider* collider;
    float inverseMass; // Inverse for optimisation and representing infinite mass
};

#endif