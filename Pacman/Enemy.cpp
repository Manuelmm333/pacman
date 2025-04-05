#include "Enemy.h"
#include "Player.h"
#include <cstring>
#include <iostream>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>

Enemy::Enemy(Scene& scene) : Entity(), m_scene(scene) {
    setMovementSpeed(3.0f); // Los fantasmas son un poco más lentos que el jugador
}

const char* Enemy::getName() const
{
    return "Enemy";
}

void Enemy::onCollision(const Entity* other)
{
    if (strcmp(other->getName(), "Player") == 0 && m_window != nullptr)
    {
        m_window->close();
    }
}

void Enemy::handleInput() {
    updateMovement();
}

void Enemy::updateMovement() {
    Vector2 currentPos = getPosition();
    float minDistance = CHASE_DISTANCE;
    Vector2 targetPos = currentPos;

    // Buscar al jugador en la escena
    for (const auto& entity : m_scene.getEntities()) {
        if (strcmp(entity->getName(), "Player") == 0) {
            Vector2 playerPos = entity->getPosition();
            float distance = std::sqrt(
                (playerPos.x - currentPos.x) * (playerPos.x - currentPos.x) +
                (playerPos.y - currentPos.y) * (playerPos.y - currentPos.y)
            );
            
            if (distance < minDistance) {
                minDistance = distance;
                targetPos = playerPos;
            }
        }
    }

    // Calcular dirección hacia el objetivo
    Vector2 direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        // Normalizar la dirección
        direction.x /= distance;
        direction.y /= distance;

        // Mover hacia el objetivo
        Vector2 newPosition = currentPos;
        newPosition.x += direction.x * getMovementSpeed();
        newPosition.y += direction.y * getMovementSpeed();

        setPosition(newPosition.x, newPosition.y);
    }
}
