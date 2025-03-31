#pragma once

class Entity;

class Component
{
public:
  Component() = default;
  virtual ~Component() = default;

  virtual void update(const Entity* parent/*DeltaTime*/) = 0;
};

