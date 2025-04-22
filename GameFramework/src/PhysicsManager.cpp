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
    // Aqui ya que entity es un shared pointer, podrías usar el cast de la std
    // de esta forma evitas el uso de punteros crudos
    //if (dynamic_cast<WallEntity*>(entity.get()))
    if (std::dynamic_pointer_cast<WallEntity>(entity))
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
      const sf::FloatRect intersectionBounds = intersection.value();
      const Vector2 &entityPosition = entity->getPosition();

      const bool isHorizontalCollision = intersectionBounds.size.x < intersectionBounds.size.y;
      
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