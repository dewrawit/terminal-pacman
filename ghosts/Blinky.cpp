#include "Ghost.h"
#include "Blinky.h"
#include "../core/GameState.h"
#include "../core/AsciiData.h"
#include "../core/Timer.h"
#include "../core/Position.h"
#include "../core/Board.h"
#include "../core/LevelInfo.h"
#include "../core/ColorData.h"

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
    else if(m_state == GhostState::dead)
    {
        m_target = LevelInfo::ghostSpawn;
    }
    else
    {
        m_target = gameState.getPacman().getPosition();
    }
}