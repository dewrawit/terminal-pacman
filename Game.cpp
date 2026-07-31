#include "Entity.h"
#include "GameState.h"
#include "Game.h"
#include "Position.h"
#include <iostream>
#include <string>
#include <cctype>

namespace Game
{
    using uchar = unsigned char;

    bool validDirection( Entity::Direction direction, const GameState& gameState)
    {
        //If pacman after moving in this direction a tile and hits a wall, it's invalid
        const Board& board { gameState.getBoard() };
        const Position& currentPacmanPosition { gameState.getPacman().getPosition() };

        return board.getTileAtPosition (
            currentPacmanPosition + Entity::getDirectionOffset(direction)
        ).isWalkable();
    }
    Entity::Direction getDirectionPlayer(const GameState& gameState)
    {   
        while(true)
        {
            std::cout << "Enter (W,A,S,D): ";
            std::string input{};
            std::getline(std::cin >> std::ws, input);

            //Remove trailing whitespace
            while(std::isspace(static_cast<uchar>(input.back())))
            {
                input.pop_back();
            }

            if(input.length() != 1)
            {
                continue;
            }

            std::cout << "Pass the check\n";

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
}