#pragma once

#include <vector>
#include <memory>

class Component;

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

 private:
  std::vector<std::shared_ptr<Component>> m_components;
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

