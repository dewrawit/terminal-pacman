#include "Entity.h"
#include "GameState.h"
#include "Game.h"
#include "Position.h"
#include "AsciiData.h"
#include "../ghosts/AllGhosts.h"
#include "Tile.h"
#include "../saveSystem/SaveSystem.h"
#include <iostream>
#include <string>
#include <cctype>
#include <print>
#include <thread>
#include <cmath>

namespace Game
{
    using uchar = unsigned char;
    using namespace std::chrono_literals;

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
                    gameState.incrementGhostConsumedStacks();

                    //Points for each stacks 200 -> 400 -> 800 -> 1600
                    gameState.increaseScore(
                        100 * static_cast<int>(std::pow(2, gameState.getGhostConsumedStacks()))
                    );
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
        std::println("\nAll pellets captured, you win!\n");
    }
    void printLoseMessage()
    {
        std::println("\nOut of lives, GAME OVER!\n");
    }
    void printThankMessage()
    {
        std::println("\nThank you for playing!\n");
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
    void saveGame(const SaveSystem& saveSystem, const GameState& gameState)
    {
        std::string userName { inputUserName() };

        std::println("Adding your score to leaderboard...\n");

        std::this_thread::sleep_for(2s);

        saveSystem.save(userName, gameState.getScore());
    }
    void loadLeaderBoard(const SaveSystem& saveSystem)
    {
        saveSystem.loadLeaderboard();
    }
    void saveScoreAndShowLeaderBoard(const SaveSystem& saveSystem, const GameState& gameState)
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
        std::println("\n===============================\n");

        std::print("Enter your name (3 alphabets): ");

        while(true)
        {
            bool valid { true };
            std::string input{ getStripString() };
            
            if(input.length() != 3)
            {
                std::print("Invalid name length, try again: ");
                valid = false;
            }

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
            {
                std::println("\n===============================\n");
                for(auto& letter : input)
                {
                    letter = static_cast<char>(std::toupper(static_cast<uchar>(letter)));
                }
                return input;
            }
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
    void checkHighScore(const SaveSystem& saveSystem, const GameState& gameState)
    {
        std::println("===============================\n");
        if(gameState.getScore() >= saveSystem.getHighScore())
        {
            std::println("      NEW RECORD! {}\n", gameState.getScore());
        }
        else
        {
            std::println("      Your score: {}\n", gameState.getScore());
        }
        std::println("===============================\n");
    }
}