#include "PhysicsManager.h"
#include "Scene.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "WallEntity.h"

#include <iostream>

void PhysicsManager::handleCollisions(const Scene &scene)
{
  const std::vector<std::shared_ptr<Entity>> &entities = scene.getEntities();

  for (const auto &entity : entities)
  {
    if (dynamic_cast<WallEntity*>(entity.get()))
    {
      continue;
    }

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

      // Check for intersection between the two entities
      std::optional intersection = physics->getBounds().findIntersection(otherPhysics->getBounds());
      if (!intersection.has_value())
      {
        continue;
      }

      // Get the intersection bounds
      sf::FloatRect intersectionBounds = intersection.value();
      const Vector2 &entityPosition = entity->getPosition();

      bool isHorizontalCollision = intersectionBounds.size.x < intersectionBounds.size.y;
      
      if (isHorizontalCollision)
      {
        if (entityPosition.x < otherEntity->getPosition().x)
        {
          entity->setPosition(entityPosition.x - intersectionBounds.size.x, entityPosition.y);
        }
        else
        {
          entity->setPosition(entityPosition.x + intersectionBounds.size.x, entityPosition.y);
        }
      }
      else
      {
        if (entityPosition.y < otherEntity->getPosition().y)
        {
          entity->setPosition(entityPosition.x, entityPosition.y - intersectionBounds.size.y);
        }
        else
        {
          entity->setPosition(entityPosition.x, entityPosition.y + intersectionBounds.size.y);
        }
      }

      // Notify both entities of the collision
      entity->onCollision(otherEntity.get());
      otherEntity->onCollision(entity.get());
    }
  }
}