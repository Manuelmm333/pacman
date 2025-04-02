#include "MapComponent.h"
#include "Entity.h"
#include "WallEntity.h"
#include "PhysicsComponent.h"
#include <fstream>
#include <iostream>

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
  // No update logic needed for the map
}

void MapComponent::render(sf::RenderWindow &window) const
{
  for (size_t y = 0; y < m_map.size(); ++y)
  {
    for (size_t x = 0; x < m_map[y].size(); ++x)
    {
      if (m_map[y][x] == WALL_CHAR)
      {
        m_wallShape.setPosition({x * TILE_SIZE, y * TILE_SIZE});
        window.draw(m_wallShape);
      }
    }
  }
}