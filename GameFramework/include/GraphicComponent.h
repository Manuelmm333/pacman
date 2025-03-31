#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class GraphicComponent : public Component
{
 public:
  GraphicComponent(const sf::Texture& texture);
  ~GraphicComponent() = default;

  void update(const Entity* parent/*DeltaTime*/) override;

  inline void setTexture(const sf::Texture& texture) { m_sprite.setTexture(texture); }

  inline const sf::Sprite& getSprite() const{  return m_sprite; }

 private:
  sf::Sprite m_sprite;
};