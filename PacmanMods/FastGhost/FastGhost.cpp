#include "FastGhost.h"
#include <iostream>

#ifdef _WIN32
#define DYNAMIC_LIBRARY_API __declspec(dllexport)
#else
#define DYNAMIC_LIBRARY_API __attribute__((visibility("default")))
#endif

extern "C" DYNAMIC_LIBRARY_API void loadMod(Entity* entity) {
    if (entity != nullptr) {
        float currentSpeed = entity->getMovementSpeed();
        entity->setMovementSpeed(currentSpeed * 1.5f); 
        std::cout << "FastGhost mod applied! New speed: " << entity->getMovementSpeed() << std::endl;
    }
} 