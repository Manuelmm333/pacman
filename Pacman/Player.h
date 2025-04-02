#pragma once
#include "Entity.h"
#include <iostream>

class Player : public Entity
{
public:
  const char* getName() const override { return "Player"; }
  
  void onCollision(const Entity* other) override
  {
    std::cout << "Player collided with " << other->getName() << std::endl;
  }
}; 