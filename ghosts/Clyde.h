#pragma once

#include "Ghost.h"

class Clyde : public Ghost
{
    public:
    Clyde(const Position& pos) 
        : Ghost{ "Clyde", AsciiData::ClydeSymbol, pos, Color::ORANGE,
            Timer(30, Timer::TimerTypes::stalemate)}
    { }
};