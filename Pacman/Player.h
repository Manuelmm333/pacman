#pragma once
#include "Entity.h"
#include <SFML/Window/Keyboard.hpp>

class Player : public Entity
{
public:
    Player();
    ~Player() override = default;

    void handleInput() override;
    constexpr char* getName() const override { return "Player"; }
    void onCollision(const Entity* other) override;
}; 