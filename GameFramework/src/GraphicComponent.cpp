#include "GraphicComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Vector2.h"

GraphicComponent::GraphicComponent(const sf::Texture& texture)
 : m_sprite(texture) 
{
  sf::Vector2u textureSize = texture.getSize();
  float scale = 32.0f / textureSize.x;
  m_sprite.setScale({scale, scale});
}

void GraphicComponent::update(const Entity* parent/*DeltaTime*/)
{
  if (parent && parent->isDirty())
  {
    const Vector2& position = parent->getPosition();
    sf::Vector2f newPosition(position.x, position.y);
    m_sprite.setPosition(newPosition);
  }
}
