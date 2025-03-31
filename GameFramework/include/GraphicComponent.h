#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class GraphicComponent : public Component
{
 public:
  GraphicComponent(const sf::Texture& texture);
  ~GraphicComponent() = default;

  void update(const Entity* parent/*DeltaTime*/) override;

  inline const sf::Sprite& getSprite() const{
    return m_sprite;
  }

 private:
  sf::Sprite m_sprite;
};