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
    constexpr int pinkyTargetRange { 4 };

    Position pacmanPosition { gameState.getPacman().getPosition() };
    Direction facingDirection { gameState.getPacman().getDirection() };

    m_target = pacmanPosition;

    for(int step {0}; step < pinkyTargetRange; ++step)
    {
        m_target = m_target + getDirectionOffset(facingDirection);
    }
}