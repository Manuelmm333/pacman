#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    ~Player() override = default;

    const char* getName() const override;
    void onCollision(const Entity* other) override;
}; 