#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <filesystem>

#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "Entity.h"
#include "PhysicsManager.h"
#include "GraphicComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "ScriptComponent.h"

const std::string ASSETS_PATH = "./Assets/";
static bool isDebug = true;

typedef void (*ComponentScript)(const Entity* parent);
typedef ComponentScript(*LoadModFunc)();

void updateScene(const Scene& scene);
void renderScene(const Scene& scene, sf::RenderWindow& window);
void loadMods(const Scene& scene, Entity* player);

int main()
{
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(144);

  sf::Texture pacmanTexture(ASSETS_PATH + "pacman.png");

  std::shared_ptr<Entity> player = std::make_shared<Entity>();
  player->addComponent<GraphicComponent>(pacmanTexture);
  player->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(130.0f, 130.0f));
  
  std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
  enemy->addComponent<GraphicComponent>(pacmanTexture);
  enemy->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(130.0f, 130.0f));

  enemy->setPosition(150.0f, 150.0f);

  Scene scene;
  scene.addEntity(player);
  scene.addEntity(enemy);

  PhysicsManager physicsManager;


  while (window.isOpen())
  {
    sf::Color pink(255, 192, 203);
    window.clear(pink);

    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
      const Vector2& playerPosition = player->getPosition();
      player->setPosition(playerPosition.x - 1.0f, playerPosition.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {

      const Vector2& playerPosition = player->getPosition();
      player->setPosition(playerPosition.x + 1.0f, playerPosition.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {

      const Vector2& playerPosition = player->getPosition();
      player->setPosition(playerPosition.x, playerPosition.y - 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {

      const Vector2& playerPosition = player->getPosition();
      player->setPosition(playerPosition.x, playerPosition.y + 1.0f);
    }

    updateScene(scene);
    renderScene(scene, window);

    physicsManager.handleCollisions(scene);

    window.display();
  }
}

void updateScene(const Scene& scene)
{
  for (const auto& entity : scene.getEntities())
  {
    entity->update(/*DeltaTime*/);
  }
}

void renderScene(const Scene& scene, sf::RenderWindow& window)
{
  //render scene
  for (const auto& entity : scene.getEntities())
  {
    std::weak_ptr<GraphicComponent> graphicComponentWeak = entity->getComponent<GraphicComponent>();
    if (const std::shared_ptr<GraphicComponent> graphicComponent = graphicComponentWeak.lock())
    {
      const sf::Sprite& sprite = graphicComponent->getSprite();
      window.draw(sprite);
    }

    if (isDebug) 
    {
      std::weak_ptr<PhysicsComponent> physicsComponentWeak = entity->getComponent<PhysicsComponent>();
      if (const std::shared_ptr<PhysicsComponent> physicsComponent = physicsComponentWeak.lock())
      {
        const sf::FloatRect& bounds = physicsComponent->getBounds();
        sf::RectangleShape debugShape(sf::Vector2f(bounds.size.x, bounds.size.y));
        debugShape.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
        debugShape.setFillColor(sf::Color::Transparent);
        debugShape.setOutlineColor(sf::Color::Red);
        debugShape.setOutlineThickness(1.0f);
        window.draw(debugShape);
      }
    }
  }
}