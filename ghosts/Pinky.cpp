#include "Ghost.h"
#include "Pinky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"

Pinky::Pinky(const Position& pos) 
        : Ghost{ "Pinky", AsciiData::PinkySymbol, pos, Color::PINK,
            Timer(10, Timer::TimerTypes::stalemate)} 
    { }
void Pinky::setTarget(GameState& gameState)
{
    //Targets 4 tiles ahead
    constexpr int targetRange { 4 };

    Position pacmanPosition { gameState.getPacman().getPosition() };
    Direction facingDirection { gameState.getPacman().getDirection() };

    auto [ offsetx, offsety ] { getDirectionOffset(facingDirection) };

    m_target = pacmanPosition + std::pair{ offsetx * targetRange, offsety * targetRange };
}