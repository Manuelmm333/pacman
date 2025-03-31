#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Vector2.h"

PhysicsComponent::PhysicsComponent(sf::Vector2f position, sf::Vector2f size)
  : m_bounds(position, size) {}


void PhysicsComponent::update(const Entity* parent/*DeltaTime*/)
{
  if (parent && parent->isDirty())
  {
    const Vector2& position = parent->getPosition();
    m_bounds.position = sf::Vector2(position.x, position.y);
  }
}

