#include "GraphicComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Vector2.h"

GraphicComponent::GraphicComponent(const sf::Texture& texture)
 : m_sprite(texture) {}

void GraphicComponent::update(const Entity* parent/*DeltaTime*/)
{
  if (parent && parent->isDirty())
  {
    const Vector2& position = parent->getPosition();
    sf::Vector2f newPosition(position.x, position.y);
    m_sprite.setPosition(newPosition);
  }
}
