#pragma once

#include "Ghost.h"

class Pinky : public Ghost
{
    public:
    Pinky(const Position& pos) 
        : Ghost{ "Pinky", AsciiData::PinkySymbol, pos, Color::PINK,
            Timer(10, Timer::TimerTypes::stalemate)} 
        
    { }
};