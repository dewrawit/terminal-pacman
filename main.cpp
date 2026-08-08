
#include "GameState.h"
#include "Game.h"
#include "Entity.h"
#include "Timer.h"
#include "SaveSystem.h"


int main()
{
    constexpr bool shouldEndGame { true };
    
    GameState gameState{ LevelInfo::map };
    gameState.activateTimerState(Timer::TimerTypes::scatter);
    gameState.startGhostsWaitTimer();

    while(true)
    {
        gameState.renderBoard();
        Entity::Direction directionInput { Game::getDirectionPlayer(gameState) };

        gameState.getPacman().move(directionInput);
        
        //Check collision, win, lose, respawn
        if(Game::handlePacmanCollision(gameState) == shouldEndGame)
        {
            break;
        }

        //update global timer, ghost wait timer (teleport out of house if timeout), ghost speed
        gameState.update();

        //Ghost AI shit
        gameState.retargetGhosts();

        //Ghost move
        gameState.moveGhosts();

        if(Game::handlePacmanCollision(gameState) == shouldEndGame)
        {
            break;
        }
    }

    SaveSystem saveSystem{};
    if(Game::chooseSaveGame())
    {
        Game::saveGame(saveSystem);
    }
    return 0;
}