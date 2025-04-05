#pragma once

#include <vector>
#include <memory>
#include "Vector2.h"

#ifdef __linux__

# define DYNAMIC_LIBRARY_API __attribute__((visibility("default")))

#else // Windows

# ifdef DYNAMIC_LIBRARY_EXPORTS
#   define DYNAMIC_LIBRARY_API __declspec(dllexport)
# else 
#   define DYNAMIC_LIBRARY_API __declspec(dllimport)
# endif // DYNAMIC_LIBRARY_EXPORTS

#endif // __linux__

class Component;
class Scene;

class Entity
{
public:
  Entity();
  virtual ~Entity() = default; 

  template <typename T = Component, typename... Args>
  std::weak_ptr<T> addComponent(Args&&... args);

  template <typename T>
  std::weak_ptr<T> getComponent() const;

  void update(/*DeltaTime*/);
  virtual void handleInput() {} // Default empty implementation

  virtual void onCollision(const Entity* other);

  void setPosition(float x, float y);
  const Vector2& getPosition() const;

  virtual const char* getName() const { return "Entity"; }

  inline bool isDirty() const { return m_isDirty; }

  float getMovementSpeed() const { return m_movementSpeed; }
  void setMovementSpeed(float speed) { m_movementSpeed = speed; }

protected:
  static constexpr float DEFAULT_MOVEMENT_SPEED = 4.0f;
  float m_movementSpeed = DEFAULT_MOVEMENT_SPEED;

private:
  std::vector<std::shared_ptr<Component>> m_components;
  Vector2 m_position;
  bool m_isDirty = false;
};

template <typename T, typename... Args>
std::weak_ptr<T> Entity::addComponent(Args&&... args)
{
  std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
  m_components.push_back(component);
  return component;
}

template <typename T>
std::weak_ptr<T> Entity::getComponent() const
{
  for (const auto& component : m_components)
  {
    std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
    if (castedComponent)
    {
      return castedComponent;
    }
  }

  return std::weak_ptr<T>();
}

