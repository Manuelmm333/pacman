#include "GraphicComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

GraphicComponent::GraphicComponent(const sf::Texture& texture)
 : m_sprite(texture) {}

void GraphicComponent::update(const Entity* parent/*DeltaTime*/)
{
  if (parent)
  {
    std::weak_ptr<Transform> transformWeak = parent->getComponent<Transform>();
    if (auto transform = transformWeak.lock())
    {
      sf::Vector2f newPosition(transform->position.x, transform->position.y);
      m_sprite.setPosition(newPosition);
    }
  }
}

