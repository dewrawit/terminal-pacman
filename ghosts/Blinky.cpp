#include "Ghost.h"
#include "Blinky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"

Blinky::Blinky(const Position& pos) 
        : Ghost{ "Blinky", AsciiData::BlinkySymbol, pos, Color::RED, 
            Timer(0, Timer::TimerTypes::stalemate)}
    { }