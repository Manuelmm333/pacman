#pragma once

#include "Component.h"
#include <SFML/Graphics/Rect.hpp>

class Entity;

class PhysicsComponent : public Component
{
public:
  PhysicsComponent() = default;
  PhysicsComponent(sf::Vector2f position, sf::Vector2f size);
  ~PhysicsComponent() override = default;

  void update(const Entity* parent/*DeltaTime*/) override;

  void setBounds(const sf::FloatRect& bounds) { m_bounds = bounds; }
  const sf::FloatRect& getBounds() const { return m_bounds; }


  private: 
  sf::FloatRect m_bounds;
};