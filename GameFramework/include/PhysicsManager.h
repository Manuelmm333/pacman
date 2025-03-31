#pragma once

class Scene;

class PhysicsManager
{
public:
  PhysicsManager() = default;
  ~PhysicsManager() = default;

  void handleCollisions(const Scene& scene);
};