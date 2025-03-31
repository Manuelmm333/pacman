#pragma once

#include "Component.h"
#include "Vector2.h"

class Transform : public Component
{
public:
  Transform() = default;
  ~Transform() = default;

  void update(const Entity* parent/*DeltaTime*/) override;

 private:
  friend class Entity;
  
  Vector2 position;
  Vector2 scale;
  float rotation = 0.0f;
};