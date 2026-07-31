
#include "GameState.h"
#include "Game.h"
#include "Entity.h"

int main()
{
    Board board{LevelInfo::map};
    GameState gameState{board};

    while(true)
    {
        gameState.getBoard().draw();
        //Entity::Direction directionInput { Game::getDirectionPlayer(gameState) };

        //Move pacman
        
        //Check collision (also check win)

        //Ghost AI shit

        //Ghost move

        //Check collision again
    }
    
    
    return 0;
}