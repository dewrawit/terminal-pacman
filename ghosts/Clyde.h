#pragma once

#include "Ghost.h"

struct Position;

class Clyde : public Ghost
{
    public:
    Clyde(const Position& pos);
    void setTarget(GameState& gameState) override;
};