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
    void saveGame(SaveSystem& saveSystem, const GameState& gameState);
    void loadLeaderBoard(const SaveSystem& saveSystem);
    void saveScoreAndShowLeaderBoard(SaveSystem& saveSystem, const GameState& gameState);
    void printThankMessage();
    std::string inputUserName();
}