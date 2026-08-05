#pragma once

#include "Ghost.h"

class Pinky : public Ghost
{
    public:
    Pinky(const Position& pos);
    void setTarget(GameState& gameState) override;
};