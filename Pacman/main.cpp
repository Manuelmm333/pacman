#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "Entity.h"
#include "GraphicComponent.h"
#include "TransformComponent.h"

const std::string ASSETS_PATH = "./Assets/";

void updateScene(const Scene& scene);
void renderScene(const Scene& scene, sf::RenderWindow& window);

int main()
{
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
  window.setFramerateLimit(144);

  sf::Texture pacmanTexture(ASSETS_PATH + "pacman.png");

  std::shared_ptr<Entity> player = std::make_shared<Entity>();
  player->addComponent<GraphicComponent>(pacmanTexture);

  std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
  enemy->addComponent<GraphicComponent>(pacmanTexture);

  std::weak_ptr<Transform> playerTransformWeak = player->getComponent<Transform>();
  std::shared_ptr<Transform> playerTransform = playerTransformWeak.lock();

  Scene scene;
  scene.addEntity(player);
  scene.addEntity(enemy);

  while (window.isOpen())
  {
    sf::Color pink(255, 192, 203);
    window.clear(pink);

    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
      playerTransform->position.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
      playerTransform->position.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
      playerTransform->position.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
      playerTransform->position.y += 1.0f;
    }

    updateScene(scene);
    renderScene(scene, window);

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
  }
}