#include "Entity.h"
#include "GameState.h"
#include "Game.h"
#include "Position.h"
#include "AsciiData.h"
#include "ghosts/AllGhosts.h"
#include "Tile.h"
#include "SaveSystem.h"
#include <iostream>
#include <string>
#include <cctype>
#include <print>
#include <thread>

namespace Game
{
    using uchar = unsigned char;

    bool validDirection(const Entity& entity, Entity::Direction direction, const GameState& gameState)
    {
        //If pacman after moving in this direction a tile and hits a wall, it's invalid
        const Board& board { gameState.getBoard() };
        const Position currentPosition { entity.getPosition() };
        const Position newPosition { 
            currentPosition + Entity::getDirectionOffset(direction) 
        };

        //Going into Side tunnel (valid) is the only way to make position out of bounds 
        //Because wall block any other path
        if(newPosition.outOfBounds()) 
        {
            return true;
        }

        //DEBUG
        //std::cout << currentPacmanPosition << '\n';
        //std::cout << newPosition << '\n';

        return board.getTileAtPosition(newPosition).isWalkable();
    }
    Entity::Direction getDirectionPlayer(const GameState& gameState)
    {   
        while(true)
        {
            std::cout << "Enter (W,A,S,D): ";
            std::string input{ getStripString() };

            if(input.length() != 1)
            {
                continue;
            }

            Entity::Direction directionInput {};

            switch(std::tolower(static_cast<uchar>(input[0])))
            {
                case 'w': directionInput = Entity::Direction::up; break;
                case 'a': directionInput = Entity::Direction::left; break;
                case 's': directionInput = Entity::Direction::down; break;
                case 'd': directionInput = Entity::Direction::right; break;
                default: continue;
            }

            if(validDirection(gameState.getPacman(), directionInput, gameState))
                return directionInput;
            else
            {
                std::cout << "Cannot move there.\n";
            }
        }
    }
    bool handlePacmanCollision(GameState& gameState)
    {
        using namespace std::chrono_literals;

        Pacman& pacman { gameState.getPacman() };
        const Position pacmanPosition { pacman.getPosition() };
        
        Tile collidedTile { 
            gameState.getBoard().getTileAtPosition(pacmanPosition)
        };

        //Ghost should be highest priority
        for(auto& ghostPtr : gameState.getGhosts())
        {
            if(ghostPtr->getPosition() == pacmanPosition)
            {
                if(gameState.ghostAt(pacmanPosition).isScared() || 
                gameState.ghostAt(pacmanPosition).isDead())
                {
                    gameState.ghostAt(pacmanPosition).setState(Ghost::GhostState::dead);
                }
                else //Collide with healthy ghost 
                {
                    //reset level, lose a life, check loss
                    gameState.loseALife();

                    gameState.renderBoard();

                    if(gameState.lose())
                    {
                        Game::printLoseMessage();
                        return true;
                    }

                    std::println("\nYou collided with {}! Respawning shortly...", 
                        ghostPtr->getName());

                    std::this_thread::sleep_for(2s);

                    gameState.respawn();
                    return false;
                }
            }
        }

        if(gameState.containsPelletAt(pacmanPosition))
        {
            if(gameState.pelletAt(pacmanPosition).isSuperPellet())
            {
                gameState.activateTimerState(Timer::TimerTypes::scared);
                for(auto& ghostPtr : gameState.getGhosts())
                {
                    if(!ghostPtr->isScared() && !ghostPtr->isDead())
                        ghostPtr->flipDirection();
                }
            }
            gameState.removePelletAt(pacmanPosition);
            gameState.increaseScore(100);
            if(gameState.win())
            {
                Game::printWinMessage();
                return true;
            }
        }
        return false;
    }
    void printWinMessage()
    {
        std::println("All pellets captured, you win!\n");
    }
    void printLoseMessage()
    {
        std::println("Out of lives, GAME OVER!\n");
    }
    void printThankMessage()
    {
        std::println("Thank you for playing!\n");
    }
    bool chooseSaveGame()
    {
        while(true)
        {
            std::print("Would you like to add your score to the leaderboard? [y/n]:  ");
            std::string input{ getStripString() };

            if(input.length() != 1)
            {
                continue;
            }

            switch(input[0])
            {
                case 'y':
                case 'Y':
                    return true;
                case 'n':
                case 'N':
                    return false;
                default: continue;
            }
        }
    }
    void saveGame(SaveSystem& saveSystem, const GameState& gameState)
    {
        std::string userName { inputUserName() };

        std::println("Adding your score to leaderboard...");

        saveSystem.save(userName, gameState.getScore());
        std::println("Score saved.");
    }
    void loadLeaderBoard(const SaveSystem& saveSystem)
    {
        saveSystem.loadLeaderboard();
    }
    void saveScoreAndShowLeaderBoard(SaveSystem& saveSystem, const GameState& gameState)
    {
        try
        {
            saveGame(saveSystem, gameState);
            loadLeaderBoard(saveSystem);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::string inputUserName()
    {
        std::print("Enter your name (No spaces or special symbols): ");

        while(true)
        {
            bool valid { true };
            std::string input{ getStripString() };
            
            for(auto c : input)
            {
                if(!std::isalpha(static_cast<uchar>(c)))
                {
                    valid = false;
                    std::print("Name must not contain spaces or special symbols: ");
                    break;
                }
            }

            if(valid)
                return input;
        }
    }
    std::string getStripString()
    {
        std::string input{};
        std::getline(std::cin >> std::ws, input);

        //Remove trailing whitespace
        while(!input.empty() && std::isspace(static_cast<uchar>(input.back())))
        {
            input.pop_back();
        }

        return input;
    }   
}