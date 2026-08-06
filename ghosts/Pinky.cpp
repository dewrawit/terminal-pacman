#include "Ghost.h"
#include "Pinky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"
#include "../LevelInfo.h"
#include "../ColorData.h"

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