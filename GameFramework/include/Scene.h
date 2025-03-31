#pragma once

#include <vector>
#include <memory>

class Entity;

class Scene
{
public:
  Scene() = default;
  ~Scene() = default;

  void addEntity(std::shared_ptr<Entity> entity);

  inline const std::vector<std::shared_ptr<Entity>>&
  getEntities() const{
    return m_entities;
  }

private:
  std::vector<std::shared_ptr<Entity>> m_entities;
};


