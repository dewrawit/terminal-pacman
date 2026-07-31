#include "Entity.h"
#include "GameState.h"

namespace Game
{
    bool validDirection( Entity::Direction direction, const GameState& gameState);
    Entity::Direction getDirectionPlayer(const GameState& gameState);
}