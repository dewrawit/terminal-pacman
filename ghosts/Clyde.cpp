#include "Ghost.h"
#include "Clyde.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"

Clyde::Clyde(const Position& pos) 
        : Ghost{ "Clyde", AsciiData::ClydeSymbol, pos, Color::ORANGE,
            Timer(30, Timer::TimerTypes::stalemate)}
    { }
void Clyde::setTarget(GameState& gameState)
{

}