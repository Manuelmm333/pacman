#pragma once

#include "Component.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Scene.h"

class MapComponent : public Component
{
public:
    MapComponent(const std::string& mapPath, Scene& scene);
    ~MapComponent() = default;

    void update(const Entity* parent/*DeltaTime*/) override;
    void render(sf::RenderWindow& window) const;

private:
    void loadMap(const std::string& mapPath);
    void createWallEntities();

    static constexpr float TILE_SIZE = 32.0f;
    static constexpr char WALL_CHAR = '#';
    static constexpr char EMPTY_CHAR = '.';

    std::vector<std::vector<char>> m_map;
    std::vector<std::shared_ptr<Entity>> m_wallEntities;
    mutable sf::RectangleShape m_wallShape;
    Scene& m_scene;
}; 