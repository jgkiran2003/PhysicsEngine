#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Vector3.h"
#include "Collider.h"

class PhysicsObject {
  public:
    // Constructor
    PhysicsObject(Collider* collider, const Vector3& vel = Vector3(0, 0, 0), const float mass = 1.0f) :
      collider(collider),
      velocity(vel),
      forceAccumulator(Vector3(0, 0, 0))
    {
      if (mass <= 0.0f) {
        inverseMass = 0.0f; // This represents infinite mass (immovable)
      } else {
        inverseMass = 1.0f / mass;
      }
    }

    // Destructor
    ~PhysicsObject();

    // Movement
    void Integrate(float delta);

    void AddForce(const Vector3& force) {
      forceAccumulator = forceAccumulator + force;
    }

    void ClearForceAccumulator() {
      forceAccumulator = Vector3(0, 0, 0);
    }

    // Getters
    inline Vector3 GetPosition() const { return collider->GetCenter(); }
    inline Vector3 GetVelocity() const { return velocity; }
    inline Collider& GetCollider() { return *collider; }
    inline float GetInvMass() const { return inverseMass; }

    // Setters
    inline void SetVelocity(const Vector3& vel) { velocity = vel; }
  
  private:
    Vector3 velocity;
    Collider* collider;
    float inverseMass; // Inverse for optimisation and representing infinite mass

    Vector3 forceAccumulator;
};

#endif