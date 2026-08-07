#include "Ghost.h"
#include "Inky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"
#include "../LevelInfo.h"
#include "../ColorData.h"

Inky::Inky(const Position& pos) 
        : Ghost{ "Inky", AsciiData::InkySymbol, pos, Color::CYAN,
            Timer("Wait",20, Timer::TimerTypes::stalemate)}
    { }
void Inky::setTarget(GameState& gameState)
{
    if(m_state == GhostState::scatter)
    {
        m_target = LevelInfo::inkyCorner;
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
        constexpr int targetAhead { 2 };

        Position pacmanPosition { gameState.getPacman().getPosition() };
        Direction facingDirection { gameState.getPacman().getDirection() };

        auto [ offsetx, offsety ] { getDirectionOffset(facingDirection) };

        Position pointAhead { 
            pacmanPosition + std::pair{ offsetx * targetAhead, offsety * targetAhead}
        };
        Position blinkyPosition { gameState.getBlinky().getPosition() };

        //Inky target: tip of vector 2 * (blinky -> pointAhead)
        // = blinky + vector( 2 * blinky -> pointahead)
        
        Position doubleVector { (pointAhead - blinkyPosition) + (pointAhead - blinkyPosition) };
        Position tip { blinkyPosition + doubleVector };

        m_target = tip;
    }
}