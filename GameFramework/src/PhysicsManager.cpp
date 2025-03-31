#include "PhysicsManager.h"
#include "Scene.h"
#include "Entity.h"
#include "PhysicsComponent.h"

#include <iostream>

void PhysicsManager::handleCollisions(const Scene &scene)
{
  const std::vector<std::shared_ptr<Entity>> &entities = scene.getEntities();

  for (const auto &entity : entities)
  {
    // Check if the entity has a PhysicsComponent
    std::weak_ptr<PhysicsComponent> physicsWeak = entity->getComponent<PhysicsComponent>();
    std::shared_ptr<PhysicsComponent> physics = physicsWeak.lock();
    if (!physics)
    {
      continue;
    }

    // Check for collisions with other entities
    for (const auto &otherEntity : entities)
    {
      if (entity == otherEntity)
      {
        continue;
      }

      std::weak_ptr<PhysicsComponent> otherPhysicsWeak = otherEntity->getComponent<PhysicsComponent>();
      std::shared_ptr<PhysicsComponent> otherPhysics = otherPhysicsWeak.lock();
      if (!otherPhysics)
      {
        continue;
      }
      std::optional intersection = physics->getBounds().findIntersection(otherPhysics->getBounds());
      if (!intersection.has_value())
      {
        continue;
      }

      // Check for collision between the two entities
      sf::FloatRect bounds = physics->getBounds();
      sf::FloatRect otherBounds = otherPhysics->getBounds();
      const Vector2 &entityPosition = entity->getPosition();
      const Vector2 &otherEntityPosition = otherEntity->getPosition();

      sf::FloatRect intersectionBounds = intersection.value();

      // horizontal
      if (intersectionBounds.size.x < intersectionBounds.size.y)
      {
        if (bounds.position.x < otherBounds.position.x)
        {
          entity->setPosition(entityPosition.x - intersectionBounds.size.x,
                              entityPosition.y);
        }
        else
        {
          entity->setPosition(entityPosition.x + intersectionBounds.size.x,
                              entityPosition.y);
        }
      }
      //vertical
      else 
      {
        if (bounds.position.y < otherBounds.position.y)
        {
          entity->setPosition(entityPosition.x,
                              entityPosition.y - intersectionBounds.size.y);
        }
        else
        {
          entity->setPosition(entityPosition.x,
                              entityPosition.y + intersectionBounds.size.y);
        }
      }

      // notify both entities of the collision
      entity->onCollision(otherEntity.get());
      otherEntity->onCollision(entity.get());
    }
  }
}