#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "GraphicComponent.h"
#include "PhysicsComponent.h"
#include "MapComponent.h"
#include "Vector2.h"

const std::string Game::WINDOW_TITLE = "Pacman";
const std::string ASSETS_PATH = "./Assets/";
static bool isDebug = true;

Game::Game()
    : m_window()
{
  m_window.create(sf::VideoMode::getDesktopMode(), WINDOW_TITLE);
  m_window.setFramerateLimit(FPS_LIMIT);
  loadResources();
  createEntities();
}

void Game::loadResources()
{
  if (!m_pacmanTexture.loadFromFile(ASSETS_PATH + "pacman.png"))
  {
    throw std::runtime_error("Failed to load pacman texture");
  }
  
  m_pacmanTexture.setSmooth(true);
}

void Game::createEntities()
{
  // Create map entity
  m_mapEntity = std::make_shared<Entity>();
  m_mapEntity->addComponent<MapComponent>(ASSETS_PATH + "map.txt", m_scene);
  m_scene.addEntity(m_mapEntity);

  // Create player
  m_player = std::make_shared<Player>();
  m_player->addComponent<GraphicComponent>(m_pacmanTexture);
  m_player->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));
  m_player->setPosition(32.0f, 32.0f); // Start at first tile
  m_scene.addEntity(m_player);

  // Create enemy
  m_enemy = std::make_shared<Entity>();
  m_enemy->addComponent<GraphicComponent>(m_pacmanTexture);
  m_enemy->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));
  m_enemy->setPosition(150.0f, 150.0f);
  m_scene.addEntity(m_enemy);
}

void Game::handleInput()
{
  const float MOVEMENT_SPEED = 4.0f; // Increased speed to match tile size better
  Vector2 newPosition = m_player->getPosition();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    newPosition.x -= MOVEMENT_SPEED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    newPosition.x += MOVEMENT_SPEED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
  {
    newPosition.y -= MOVEMENT_SPEED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
  {
    newPosition.y += MOVEMENT_SPEED;
  }

  m_player->setPosition(newPosition.x, newPosition.y);
}

void Game::update()
{
  for (const auto &entity : m_scene.getEntities())
  {
    entity->update();
  }
  m_physicsManager.handleCollisions(m_scene);
}

void Game::render()
{
  m_window.clear(sf::Color::Black);

  if (auto mapComponent = m_mapEntity->getComponent<MapComponent>().lock())
  {
    mapComponent->render(m_window);
  }

  for (const auto &entity : m_scene.getEntities())
  {
    if (entity == m_mapEntity) continue;

    std::weak_ptr<GraphicComponent> graphicComponentWeak = entity->getComponent<GraphicComponent>();
    if (const std::shared_ptr<GraphicComponent> graphicComponent = graphicComponentWeak.lock())
    {
      const sf::Sprite &sprite = graphicComponent->getSprite();
      m_window.draw(sprite);
    }

    if (isDebug)
    {
      std::weak_ptr<PhysicsComponent> physicsComponentWeak = entity->getComponent<PhysicsComponent>();
      if (const std::shared_ptr<PhysicsComponent> physicsComponent = physicsComponentWeak.lock())
      {
        const sf::FloatRect &bounds = physicsComponent->getBounds();
        sf::RectangleShape debugShape(sf::Vector2f(bounds.size.x, bounds.size.y));
        debugShape.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
        debugShape.setFillColor(sf::Color::Transparent);
        debugShape.setOutlineColor(sf::Color::Red);
        debugShape.setOutlineThickness(1.0f);
        m_window.draw(debugShape);
      }
    }
  }

  m_window.display();
}

void Game::run()
{
  while (m_window.isOpen())
  {
    while (const std::optional event = m_window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        m_window.close();
      }
    }

    handleInput();
    update();
    render();
  }
}