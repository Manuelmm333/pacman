#include "FastGhost.h"
#include <iostream>

#define DYNAMIC_LIBRARY_API __declspec(dllexport)

extern "C" DYNAMIC_LIBRARY_API void loadMod(Entity* entity) {
    if (entity != nullptr) {
        float currentSpeed = entity->getMovementSpeed();
        entity->setMovementSpeed(currentSpeed * 1.5f); 
        std::cout << "FastGhost mod applied! New speed: " << entity->getMovementSpeed() << std::endl;
    }
} 