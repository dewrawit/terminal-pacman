#include "Ghost.h"
#include "Clyde.h"
#include "../core/GameState.h"
#include "../core/AsciiData.h"
#include "../core/Timer.h"
#include "../core/Position.h"
#include "../core/Board.h"
#include "../core/LevelInfo.h"
#include "../core/ColorData.h"

Clyde::Clyde(const Position& pos) 
        : Ghost{ "Clyde", AsciiData::ClydeSymbol, pos, Color::ORANGE,
            Timer("Wait",30, Timer::TimerTypes::stalemate)}
    { }
void Clyde::setTarget(GameState& gameState)
{
    if(m_state == GhostState::scatter)
    {
        m_target = LevelInfo::clydeCorner;
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
        constexpr int chaseDistance { 8 };

        Position pacmanPosition { gameState.getPacman().getPosition() };

        if(m_pos.distance(pacmanPosition) > chaseDistance)
        {
            m_target = pacmanPosition;
        }
        else
        {
            m_target = LevelInfo::clydeCorner;
        }
    }
    
}