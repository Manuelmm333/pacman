#include "Enemy.h"
#include <iostream>
#include <cstring>
#include <SFML/Graphics/RenderWindow.hpp>

Enemy::Enemy()
{
}

const char* Enemy::getName() const
{
    return "Enemy";
}

void Enemy::onCollision(const Entity* other)
{
    if (strcmp(other->getName(), "Player") == 0 && m_window != nullptr)
    {
        // Cerrar la ventana
        m_window->close();
    }
} 