#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Scene.h"
#include "PhysicsManager.h"
#include "MapComponent.h"
#include "Enemy.h"
#include "GameManager.h"
#include <windows.h>
class Game {
public:
    Game();
    ~Game() = default;

    void run();

private:
    void handleInput();
    void update();
    void render();
    void loadResources();
    void createEntities();
    void setupGameStates();

    sf::RenderWindow m_window;
    Scene m_scene;
    PhysicsManager m_physicsManager;
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Enemy> m_enemy;
    std::shared_ptr<Enemy> m_enemy2;
    std::shared_ptr<Entity> m_mapEntity;
    sf::Texture m_pacmanTexture;
    sf::Texture m_ghostTexture;
    sf::Font m_font;
    std::string m_gameOverText;
    HMODULE mod;
    
    static const unsigned int WINDOW_WIDTH = 1920;
    static const unsigned int WINDOW_HEIGHT = 1080;
    static constexpr unsigned int FPS_LIMIT = 144;
    static const std::string WINDOW_TITLE;
}; 