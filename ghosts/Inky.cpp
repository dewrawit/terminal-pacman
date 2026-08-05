#include "Ghost.h"
#include "Inky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"

Inky::Inky(const Position& pos) 
        : Ghost{ "Inky", AsciiData::InkySymbol, pos, Color::CYAN,
            Timer(20, Timer::TimerTypes::stalemate)}
    { }
void Inky::setTarget(GameState& gameState)
{

}