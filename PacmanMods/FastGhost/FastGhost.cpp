#include "FastGhost.h"
#include <iostream>

void loadMod(Entity* entity) {
    if (entity != nullptr) {
        // Aumentar la velocidad del enemigo
        float currentSpeed = entity->getMovementSpeed();
        entity->setMovementSpeed(currentSpeed * 2.0f); // Duplicar la velocidad
        std::cout << "FastGhost mod applied! New speed: " << entity->getMovementSpeed() << std::endl;
    }
} 