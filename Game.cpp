#include "Entity.h"
#include "GameState.h"
#include "Game.h"
#include "Position.h"
#include "AsciiData.h"
#include "Tile.h"
#include <iostream>
#include <string>
#include <cctype>
#include <print>

namespace Game
{
    using uchar = unsigned char;

    bool validDirection( Entity::Direction direction, const GameState& gameState)
    {
        //If pacman after moving in this direction a tile and hits a wall, it's invalid
        const Board& board { gameState.getBoard() };
        const Position currentPacmanPosition { gameState.getPacman().getPosition() };
        const Position newPosition { 
            currentPacmanPosition + Entity::getDirectionOffset(direction) 
        };

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
            std::string input{};
            std::getline(std::cin >> std::ws, input);

            //Remove trailing whitespace
            while(!input.empty() && std::isspace(static_cast<uchar>(input.back())))
            {
                input.pop_back();
            }

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

            if(validDirection(directionInput, gameState))
                return directionInput;
            else
            {
                std::cout << "Cannot move there.\n";
            }
        }
    }
    void handlePacmanCollision(GameState& gameState)
    {
        Pacman& pacman { gameState.getPacman() };
        const Position pacmanPosition { pacman.getPosition() };
        
        Tile collidedTile { 
            gameState.getBoard().getTileAtPosition(pacmanPosition)
        };

        //Ghost should be highest priority
        if(gameState.containsGhostAt(pacmanPosition))
        {
            if(gameState.ghostAt(pacmanPosition).isScared())
            {
                gameState.ghostAt(pacmanPosition).setState(Ghost::GhostState::dead);
            }
            else
            {
                std::cout << "die" << std::endl;
                assert(false && "check");
            }
        }

        if(gameState.containsPelletAt(pacmanPosition))
        {
            if(gameState.pelletAt(pacmanPosition).isSuperPellet())
            {
                gameState.makeAllGhostsScared();
            }
            gameState.removePelletAt(pacmanPosition);
        }

    }
    void printWinMessage()
    {
        std::println("All pellets captured, you win!\n");
    }
}