#include "Player.h"
#include <iostream>

Player::Player()
{
}

const char* Player::getName() const
{
    return "Player";
}

void Player::onCollision(const Entity* other)
{
    std::cout << "Player collided with " << other->getName() << std::endl;
} 