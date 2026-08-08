#include "Entity.h"
#include "GameState.h"

class SaveSystem;

namespace Game
{
    bool validDirection(const Entity& entity, Entity::Direction direction, const GameState& gameState);
    Entity::Direction getDirectionPlayer(const GameState& gameState);
    bool handlePacmanCollision(GameState& gameState);
    void printWinMessage();
    void printLoseMessage();
    bool chooseSaveGame();
    void saveGame(const SaveSystem& saveSystem);
    void loadLeaderBoard(const SaveSystem& saveSystem);

}