#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <functional>
#include <unordered_map>

class GameManager
{
public:
    static GameManager& getInstance();
    
    // Si vas a guardar como puntero, recomiendo usar un puntero en sí.
    // incluso diría uno inteligente y guardar un weak, pero al menos si lo guardas como raw pointer
    // ser explicito y recibirlo como raw pointer
    // Incluso podrías guardarlo como const para también ser explicito que esta clase no es dueña del puntero
    void initialize(sf::RenderWindow* window);
    void update();
    void render();
    void handleEvents(const sf::Event& event);
    
    void changeState(GameState newState);
    GameState getCurrentState() const { return m_currentState; }
    
    void setStateCallback(GameState state, std::function<void()> callback);
    
private:
    GameManager() = default;
    ~GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    
    void executeStateCallback();
    
    GameState m_currentState = GameState::PLAYING;
    sf::RenderWindow* m_window = nullptr;
    std::unordered_map<GameState, std::function<void()>> m_stateCallbacks;
}; 