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

    const Board& board { gameState.getBoard() };
    Position positionToCheck { gameState.getPacman().getPosition() };
    
    Direction facingDirection { gameState.getPacman().getDirection() };

    for(int step {0}; step < pinkyTargetRange; ++step)
    {
        //Check if one tile ahead of current is a Wall or walkable
        //There shouldn't be a dead end in the map (or loop never ends since we cant go backward)
        while(true)
        {
            Position newPosition = positionToCheck + Entity::getDirectionOffset(facingDirection);

            if(board.getTileAtPosition(newPosition).isWalkable())
            {
                positionToCheck = newPosition;
                break;
            }

            //Change direction
            facingDirection = Entity::getNonOppositeRandomDirection(facingDirection);
        }
    }
    m_target = positionToCheck; //4 tiles ahead of pacman position that is walkable
}