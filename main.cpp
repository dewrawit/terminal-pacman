
#include "GameState.h"
#include "Game.h"
#include "Entity.h"
#include "Timer.h"


int main()
{
    GameState gameState{ LevelInfo::map };
    gameState.activateTimerState(Timer::TimerTypes::stalemate);

    while(true)
    {
        //also TBD: teleport tile to opposite side
        gameState.renderBoard();
        Entity::Direction directionInput { Game::getDirectionPlayer(gameState) };

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