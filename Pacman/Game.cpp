#include "Game.h"
#include "Entity.h"
#include "GraphicComponent.h"
#include "PhysicsComponent.h"
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
}

void Game::createEntities()
{
  m_player = std::make_shared<Entity>();
  m_player->addComponent<GraphicComponent>(m_pacmanTexture);
  m_player->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));

  m_enemy = std::make_shared<Entity>();
  m_enemy->addComponent<GraphicComponent>(m_pacmanTexture);
  m_enemy->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));
  m_enemy->setPosition(150.0f, 150.0f);

  m_scene.addEntity(m_player);
  m_scene.addEntity(m_enemy);
}

void Game::handleInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    const Vector2 &playerPosition = m_player->getPosition();
    m_player->setPosition(playerPosition.x - 1.0f, playerPosition.y);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    const Vector2 &playerPosition = m_player->getPosition();
    m_player->setPosition(playerPosition.x + 1.0f, playerPosition.y);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
  {
    const Vector2 &playerPosition = m_player->getPosition();
    m_player->setPosition(playerPosition.x, playerPosition.y - 1.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
  {
    const Vector2 &playerPosition = m_player->getPosition();
    m_player->setPosition(playerPosition.x, playerPosition.y + 1.0f);
  }
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

  for (const auto &entity : m_scene.getEntities())
  {
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