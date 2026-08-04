#pragma once

#include "Ghost.h"

class Blinky : public Ghost
{
    public:
    Blinky(const Position& pos) 
        : Ghost{ "Blinky", AsciiData::BlinkySymbol, pos, Color::RED, 
            Timer(0, Timer::TimerTypes::stalemate)}
    { }
};