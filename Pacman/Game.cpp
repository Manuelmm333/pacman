#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "GraphicComponent.h"
#include "PhysicsComponent.h"
#include "MapComponent.h"
#include "Vector2.h"
#include "ModManager.h"

// Buen uso de constantes!
const std::string Game::WINDOW_TITLE = "Pacman";
const std::string ASSETS_PATH = "./Assets/";
static bool isDebug = true;
typedef void(*LoadModFunction)(Entity*);

Game::Game()
    : m_window()
{
    m_window.create(sf::VideoMode::getDesktopMode(), WINDOW_TITLE);
    m_window.setFramerateLimit(FPS_LIMIT);
    
    // Al recibir el puntero ahora, necesitamos mandar su dirección de memoria
    GameManager::getInstance().initialize(&m_window);
    
    loadResources();
    createEntities();
    setupGameStates();
}

void Game::setupGameStates()
{
    auto& gameManager = GameManager::getInstance();
    
    // Menu state callback
    gameManager.setStateCallback(GameState::MENU, [this]() {
        // TODO: Implement menu logic
    });
    
    // Playing state callback
    gameManager.setStateCallback(GameState::PLAYING, [this]() {
        handleInput();
        update();
        render();
    });
    
    // Paused state callback
    gameManager.setStateCallback(GameState::PAUSED, [this]() {
        render(); // Still render the game but don't update
    });
    
    // Game Over state callback
    gameManager.setStateCallback(GameState::GAME_OVER, [this]() {
        // TODO: Implement game over logic
    });
}

void Game::loadResources()
{
    // Buen uso de chequeos. 
    // En un caso real probablemente aquí se cargarían o se generarían texturas default
    // Para evitar que el juego crashee, pero eso depende de la lógica del juego
    if (!m_pacmanTexture.loadFromFile(ASSETS_PATH + "pacman.png"))
    {
        throw std::runtime_error("Failed to load pacman texture");
    }
    
    if (!m_ghostTexture.loadFromFile(ASSETS_PATH + "fantasma.png"))
    {
        throw std::runtime_error("Failed to load ghost texture");
    }
    
    if (!m_font.openFromFile(ASSETS_PATH + "Arial.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    
    m_pacmanTexture.setSmooth(true);
    m_ghostTexture.setSmooth(true);

    // Esto estaría mejor si se cargara desde un archivo de mods, por ejemplo
    // o que se cargue desde un directorio específico, por ejemplo todo lo que esté en "Mods"
    // Así "cualquiera"podría construir un mod y meterlo ahí
    // ModManager::getInstance().loadMods();
    ModManager::getInstance().loadMod("InvisibleGhost");
    ModManager::getInstance().loadMod("FastGhost");
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
    m_player->setPosition(32.0f, 32.0f);
    m_scene.addEntity(m_player);

    // Create enemy
    m_enemy = std::make_shared<Enemy>(m_scene);
    m_enemy->addComponent<GraphicComponent>(m_ghostTexture);
    m_enemy->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));
    m_enemy->setPosition(150.0f, 150.0f);
    m_enemy->setWindow(&m_window);
    m_scene.addEntity(m_enemy);

    // Create enemy
    m_enemy2 = std::make_shared<Enemy>(m_scene);
    m_enemy2->addComponent<GraphicComponent>(m_ghostTexture);
    m_enemy2->addComponent<PhysicsComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));
    m_enemy2->setPosition(86.0f, 150.0f);
    m_enemy2->setWindow(&m_window);
    m_scene.addEntity(m_enemy2);
    ModManager::getInstance().applyMods(m_enemy2.get(), "FastGhost");

}

void Game::handleInput()
{
    // Bien! 
    // Igual para "mejor" manejo se podría hacer a través de eventos y entonces cada entidad se suscribiría
    // al evento correspondiente.Pero esto no está nada mal.
    m_player->handleInput();
    m_enemy->handleInput();
    m_enemy2->handleInput();
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

        if (entity == m_enemy)
        {
            //Aquí quizá sería mejor pensar en una forma data-driven de aplicar los mods
            // porque de esta forma se está acoplando el mod a la entidad
            // y no a la lógica del juego
            // Quizá podría venir de un archivo el en qué parte aplicarlo y el mod en sí tener info de suscripción
            ModManager::getInstance().applyMods(entity.get(), "InvisibleGhost");
        }

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
            
            GameManager::getInstance().handleEvents(*event);
        }

        GameManager::getInstance().update();
    }
}