#include <iostream>

#include "Entity.h"
#include "GraphicComponent.h"

#ifdef _WIN32
#define DYNAMIC_LIBRARY_API __declspec(dllexport)
#else
#define DYNAMIC_LIBRARY_API __attribute__((visibility("default")))
#endif

extern "C" DYNAMIC_LIBRARY_API void loadMod(Entity* entity)
{
    auto graphicComponent = entity->getComponent<GraphicComponent>();
    std::cout << entity->getName() << std::endl;
    if (auto component = graphicComponent.lock()) {
        component->getSprite().setColor(sf::Color::Transparent);
    }
}