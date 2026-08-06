
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
        gameState.renderBoard();
        Entity::Direction directionInput { Game::getDirectionPlayer(gameState) };

        gameState.getPacman().move(directionInput);
        
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
        gameState.retargetGhosts();

        //Ghost move
        gameState.moveGhosts();

        //Check collision (same as pacman check collision)
    }
    
    return 0;
}