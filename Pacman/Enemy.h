#pragma once
#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class Enemy : public Entity
{
public:
    Enemy();
    ~Enemy() override = default;

    const char* getName() const override;
    void onCollision(const Entity* other) override;
    void setWindow(sf::RenderWindow* window) { m_window = window; }
    void setFont(const sf::Font& font) { m_font = &font; }
    void setGameOverText(const std::string& text) { m_gameOverText = text; }

private:
    sf::RenderWindow* m_window = nullptr;
    const sf::Font* m_font = nullptr;
    std::string m_gameOverText;
}; 