
#include "GameState.h"
#include "Game.h"
#include "Entity.h"

int main()
{
    GameState gameState{ LevelInfo::map };

    while(true)
    {
        gameState.renderBoard();
        Entity::Direction directionInput { Game::getDirectionPlayer(gameState) };

        //Move pacman by changing position wihtout telling board yet (for collision check)
        gameState.getPacman().move(directionInput);
        
        //Check collision (deduct live if collide ghost, also check win, if win, break)
        //If die, deduct live, teleport pacman and ghost at beginning
        //If out of live, break
        Game::handlePacmanCollision(gameState);

        if(gameState.win())
        {
            Game::printWinMessage();
            break;
        }

        //TBD gotta update Tile, ghost scared cooldown blah blah blah
        gameState.update();

        

        //Ghost AI shit

        //Ghost move

        //Check collision (same as pacman check collision)
    }
    
    return 0;
}