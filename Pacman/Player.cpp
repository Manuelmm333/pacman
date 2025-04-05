#include "Player.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

Player::Player() : Entity()
{
}

void Player::handleInput() {
    Vector2 newPosition = getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        newPosition.x -= getMovementSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        newPosition.x += getMovementSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        newPosition.y -= getMovementSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        newPosition.y += getMovementSpeed();
    }

    setPosition(newPosition.x, newPosition.y);
}

void Player::onCollision(const Entity* other)
{
    std::cout << "Player collided with " << other->getName() << std::endl;
} 