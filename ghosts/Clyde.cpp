#include "Ghost.h"
#include "Clyde.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"

Clyde::Clyde(const Position& pos) 
        : Ghost{ "Clyde", AsciiData::ClydeSymbol, pos, Color::ORANGE,
            Timer(30, Timer::TimerTypes::stalemate)}
    { }
void Clyde::setTarget(GameState& gameState)
{
    constexpr int chaseDistance { 8 };

    Position pacmanPosition { gameState.getPacman().getPosition() };

    if(m_pos.distance(pacmanPosition) > chaseDistance)
    {
        m_target = pacmanPosition;
    }
    else
    {
        //scatter corner
    }
}