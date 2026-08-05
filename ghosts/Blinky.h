#pragma once

#include "Ghost.h"

struct Position;
class GameState;

class Blinky : public Ghost
{
    public:
    Blinky(const Position& pos);
    void setTarget(GameState& gameState) override;
};