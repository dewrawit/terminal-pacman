#include "Entity.h"
#include "GameState.h"

namespace Game
{
    bool validDirection(const Entity& entity, Entity::Direction direction, const GameState& gameState);
    Entity::Direction getDirectionPlayer(const GameState& gameState);
    bool handlePacmanCollision(GameState& gameState);
    void printWinMessage();
    void printLoseMessage();
}