#include "Entity.h"
#include "GameState.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <cctype>

namespace Game
{
    using uchar = unsigned char;

    bool validDirection(Entity::Direction direction, const GameState& gamestate)
    {

    }
    Entity::Direction getDirectionPlayer(const GameState& gameState)
    {
        const Pacman& pacman { gameState.getPacMan() };
        
        while(true)
        {
            std::cout << "Enter (W,A,S,D): ";
            std::string input{};
            std::getline(std::cin >> std::ws, input);

            //Remove trailing whitespace
            while(std::isspace(static_cast<uchar>(input[input.length() - 1])))
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
        }
    }
}