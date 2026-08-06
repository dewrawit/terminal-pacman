#include "Ghost.h"
#include "Blinky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"
#include "../LevelInfo.h"
#include "../ColorData.h"

Blinky::Blinky(const Position& pos) 
        : Ghost{ "Blinky", AsciiData::BlinkySymbol, pos, Color::RED, 
            Timer("Wait", 0, Timer::TimerTypes::stalemate)}
    { }

void Blinky::setTarget(GameState& gameState)
{
    //Blinky targets directly at Pacman's position
    if(m_state == GhostState::scatter)
    {
        m_target = LevelInfo::blinkyCorner;
    }
    else if(m_state == GhostState::scared)
    {
        m_target = Position::getRandomPosition();
    }
    else
    {
        m_target = gameState.getPacman().getPosition();
    }
}