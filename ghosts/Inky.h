#pragma once

#include "Ghost.h"

class Inky : public Ghost
{
    public:
    Inky(const Position& pos);
    void setTarget(GameState& gameState) override;
};