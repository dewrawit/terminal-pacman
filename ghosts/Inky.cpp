#include "Ghost.h"
#include "Inky.h"
#include "../GameState.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../Position.h"
#include "../Board.h"

Inky::Inky(const Position& pos) 
        : Ghost{ "Inky", AsciiData::InkySymbol, pos, Color::CYAN,
            Timer(20, Timer::TimerTypes::stalemate)}
    { }
void Inky::setTarget(GameState& gameState)
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