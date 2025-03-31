#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Vector2.h"

#include <iostream>

Entity::Entity()
{
  m_components.push_back(std::make_shared<Transform>());
}

void Entity::update(/*DeltaTime*/)
{
  for (const auto& component : m_components)
  {
    component->update(this/*DeltaTime*/);
  }

  m_isDirty = false;
}

void Entity::onCollision(const Entity* other)
{
  std::cout << "Collision detected with another entity!" << std::endl;
}

void Entity::setPosition(float x, float y)
{
  std::weak_ptr<Transform> transformWeak = getComponent<Transform>();
  if (std::shared_ptr<Transform> transform = transformWeak.lock())
  {
    transform->position.x = x;
    transform->position.y = y;
    m_isDirty = true;
  }
}

const Vector2& Entity::getPosition() const
{
  std::weak_ptr<Transform> transformWeak = getComponent<Transform>();
  if (std::shared_ptr<Transform> transform = transformWeak.lock())
  {
    return transform->position;
  }
  return Vector2();
}