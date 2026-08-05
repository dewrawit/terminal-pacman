#include "Ghost.h"
#include "Pinky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"

Pinky::Pinky(const Position& pos) 
        : Ghost{ "Pinky", AsciiData::PinkySymbol, pos, Color::PINK,
            Timer(10, Timer::TimerTypes::stalemate)} 
    { }
void Pinky::setTarget(GameState& gameState)
{

}