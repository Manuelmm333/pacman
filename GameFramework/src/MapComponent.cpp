#include "MapComponent.h"
#include "Entity.h"
#include "WallEntity.h"
#include "PhysicsComponent.h"
#include <fstream>
#include <iostream>

namespace MapComponentConstants
{
  static constexpr float TILE_SIZE = 32.0f;
  static constexpr char WALL_CHAR = '#';
  static constexpr char EMPTY_CHAR = '.';
} // namespace MapComponentConstants
using namespace MapComponentConstants;

MapComponent::MapComponent(const std::string &mapPath, Scene &scene)
    : m_scene(scene)
{
  // Initialize wall shape for rendering
  m_wallShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
  m_wallShape.setFillColor(sf::Color::Blue);
  m_wallShape.setOutlineColor(sf::Color::White);
  m_wallShape.setOutlineThickness(1.0f);

  loadMap(mapPath);
  createWallEntities();
}

void MapComponent::loadMap(const std::string &mapPath)
{
  std::ifstream file(mapPath);
  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open map file: " + mapPath);
  }

  std::string line;
  while (std::getline(file, line))
  {
    m_map.push_back(std::vector<char>(line.begin(), line.end()));
  }

  file.close();
}

void MapComponent::createWallEntities()
{
  for (size_t y = 0; y < m_map.size(); ++y)
  {
    for (size_t x = 0; x < m_map[y].size(); ++x)
    {
      if (m_map[y][x] == WALL_CHAR)
      {
        auto wallEntity = std::make_shared<WallEntity>();
        wallEntity->setPosition(x * TILE_SIZE, y * TILE_SIZE);
        wallEntity->addComponent<PhysicsComponent>(
            sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE),
            sf::Vector2f(TILE_SIZE, TILE_SIZE));
        m_wallEntities.push_back(wallEntity);
        m_scene.addEntity(wallEntity);
      }
    }
  }
}

void MapComponent::update(const Entity *parent /*DeltaTime*/)
{
  for (size_t y = 0; y < m_map.size(); ++y)
  {
    for (size_t x = 0; x < m_map[y].size(); ++x)
    {
      if (m_map[y][x] == WALL_CHAR)
      {
        const sf::Vector2 currentPos = m_wallShape.getPosition();
        const sf::Vector2f newPos(x * TILE_SIZE, y * TILE_SIZE);
        if (currentPos != newPos)
        {
          m_wallShape.setPosition(newPos);
        }
      }
    }
  }
}

void MapComponent::render(sf::RenderWindow &window) const
{
  for (size_t y = 0; y < m_map.size(); ++y)
  {
    for (size_t x = 0; x < m_map[y].size(); ++x)
    {
      if (m_map[y][x] == WALL_CHAR)
      {
        // Estoq uedaría mucho mejor en el update, así no tendías que 
        // poner el m_wallShape como mutable.
        // Quizá podrías incluso ponerle un diurty flag
        //m_wallShape.setPosition({x * TILE_SIZE, y * TILE_SIZE});
        window.draw(m_wallShape);
      }
    }
  }
}