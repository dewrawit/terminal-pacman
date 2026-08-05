#pragma once

#include "Ghost.h"

struct Position;

class Blinky : public Ghost
{
    public:
    Blinky(const Position& pos);
};