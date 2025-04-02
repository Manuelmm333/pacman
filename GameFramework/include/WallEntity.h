#pragma once
#include "Entity.h"

class WallEntity : public Entity
{
public:
  const char* getName() const override { return "Wall"; }
  
  void onCollision(const Entity* other) override
  {
    // Walls don't need to do anything when colliding
    // The PhysicsManager will handle moving the other entity out of the collision
  }
}; 