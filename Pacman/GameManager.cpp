#include "GameManager.h"
#include <iostream>

GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

void GameManager::initialize(sf::RenderWindow* window)
{
    m_window = window;
}

void GameManager::update()
{
    executeStateCallback();
}

void GameManager::render()
{
    if (!m_window) return;
    m_window->clear(sf::Color::Black);
    executeStateCallback();
    m_window->display();
}

void GameManager::handleEvents(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->scancode)
            {
                case sf::Keyboard::Scancode::Escape:
                    if (m_currentState == GameState::PLAYING)
                        changeState(GameState::PAUSED);
                    else if (m_currentState == GameState::PAUSED)
                        changeState(GameState::PLAYING);
                    break;
                case sf::Keyboard::Scancode::Enter:
                    if (m_currentState == GameState::MENU)
                        changeState(GameState::PLAYING);
                    break;
            }
        }
    }
}

void GameManager::changeState(GameState newState)
{
    m_currentState = newState;
    executeStateCallback();
}

void GameManager::setStateCallback(GameState state, std::function<void()> callback)
{
    m_stateCallbacks[state] = callback;
}

void GameManager::executeStateCallback()
{
    auto it = m_stateCallbacks.find(m_currentState);
    if (it != m_stateCallbacks.end())
    {
        it->second();
    }
} 