#include "Entity.h"
#include "Component.h"
#include "TransformComponent.h"

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
}