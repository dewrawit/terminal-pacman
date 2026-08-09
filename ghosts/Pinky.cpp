#include "Ghost.h"
#include "Pinky.h"
#include "../core/GameState.h"
#include "../core/AsciiData.h"
#include "../core/Timer.h"
#include "../core/Position.h"
#include "../core/Board.h"
#include "../core/LevelInfo.h"
#include "../core/ColorData.h"

Pinky::Pinky(const Position& pos) 
        : Ghost{ "Pinky", AsciiData::PinkySymbol, pos, Color::PINK,
            Timer("Wait",10, Timer::TimerTypes::stalemate)} 
    { }
void Pinky::setTarget(GameState& gameState)
{
    if(m_state == GhostState::scatter)
    {
        m_target = LevelInfo::pinkyCorner;
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
        //Targets 4 tiles ahead
        constexpr int targetRange { 4 };

        Position pacmanPosition { gameState.getPacman().getPosition() };
        Direction facingDirection { gameState.getPacman().getDirection() };

        auto [ offsetx, offsety ] { getDirectionOffset(facingDirection) };

        m_target = pacmanPosition + std::pair{ offsetx * targetRange, offsety * targetRange };
    }
}