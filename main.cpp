
#include "GameState.h"
#include "Game.h"

int main()
{
    Board board{LevelInfo::map};
    GameState gameState{board};

    gameState.getBoard().draw();

    Game::getDirectionPlayer(gameState);
    
    return 0;
}