#pragma once
#include "Entity.h"
#include "Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class Enemy : public Entity
{
public:
    Enemy(Scene& scene);
    ~Enemy() override = default;

    const char* getName() const override;
    void onCollision(const Entity* other) override;
    void handleInput() override;
    void setWindow(sf::RenderWindow* window) { m_window = window; }
    void setFont(const sf::Font& font) { m_font = &font; }
    void setGameOverText(const std::string& text) { m_gameOverText = text; }

private:
    void updateMovement();
    Scene& m_scene;
    sf::RenderWindow* m_window = nullptr;
    const sf::Font* m_font = nullptr;
    std::string m_gameOverText;
    Vector2 m_targetPosition;
    static constexpr float CHASE_DISTANCE = 200.0f;
}; 