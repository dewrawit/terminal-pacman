#pragma once

#include "Ghost.h"

class Inky : public Ghost
{
    public:
    Inky(const Position& pos) 
        : Ghost{ "Inky", AsciiData::InkySymbol, pos, Color::CYAN,
            Timer(20, Timer::TimerTypes::stalemate)}
    { }
};