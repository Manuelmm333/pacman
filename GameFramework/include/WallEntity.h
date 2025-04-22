#pragma once
#include "Entity.h"

class WallEntity : public Entity
{
public:
  // probablemente constexpr sea mejor ya que esto nunca va a cambiar
  constexpr const char* getName() const override { return "Wall"; }
  
  void onCollision(const Entity* other) override
  {
    // Walls don't need to do anything when colliding
    // The PhysicsManager will handle moving the other entity out of the collision
  }
}; 