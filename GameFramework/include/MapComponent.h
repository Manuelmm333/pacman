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

    // si estos solo los usas dentro del cpp de la clase podrían existir solo ahí, para no exponerlos:
    //static constexpr float TILE_SIZE = 32.0f;
    //static constexpr char WALL_CHAR = '#';
    //static constexpr char EMPTY_CHAR = '.';

    std::vector<std::vector<char>> m_map;
    std::vector<std::shared_ptr<Entity>> m_wallEntities;
    sf::RectangleShape m_wallShape;

    // probablemente recomendaría guardar esto como un puntero,
    // como un weak pointer, para evitar ciclos de referencia
    // o como un shared pointer. Pero tampoco está mal
    Scene& m_scene;
}; 