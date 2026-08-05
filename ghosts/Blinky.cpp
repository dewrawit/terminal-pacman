#include "Ghost.h"
#include "Blinky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"

Blinky::Blinky(const Position& pos) 
        : Ghost{ "Blinky", AsciiData::BlinkySymbol, pos, Color::RED, 
            Timer(0, Timer::TimerTypes::stalemate)}
    { }

void Blinky::setTarget(GameState& gameState)
{
    //Blinky targets directly at Pacman's position
    m_target = gameState.getPacman().getPosition();
}