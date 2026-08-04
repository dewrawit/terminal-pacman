
#include "GameState.h"
#include "Game.h"
#include "Entity.h"
#include "Timer.h"


int main()
{
    constexpr bool contactWithNonScaredGhost { true };
    
    GameState gameState{ LevelInfo::map };
    gameState.activateTimerState(Timer::TimerTypes::scatter);
    gameState.startGhostsWaitTimer();

    while(true)
    {
        //also TBD: teleport tile to opposite side
        gameState.renderBoard();
        Entity::Direction directionInput { Game::getDirectionPlayer(gameState) };

        gameState.getPacman().move(directionInput);
        
        //Check collision (deduct live if collide ghost, also check win, if win, break)
        //If die, deduct live, teleport pacman and ghost at beginning
        //If out of live, break
        
        if(Game::handlePacmanCollision(gameState) == contactWithNonScaredGhost)
        {
            //reset level, lose a life, check loss
            gameState.loseALife();
            if(gameState.lose())
            {
                Game::printLoseMessage();
                break;
            }
            gameState.respawn();
            continue;
        }

        if(gameState.win())
        {
            Game::printWinMessage();
            break;
        }

        //TBD gotta update Tile, timer blah blah blah
        gameState.update();

        //Ghost AI shit

        //Ghost move

        //Check collision (same as pacman check collision)
    }
    
    return 0;
}