#include "Entity.h"
#include "GameState.h"
#include "Game.h"
#include <iostream>

namespace Game
{
    Entity::Direction getDirectionPlayer(const GameState& gameState)
    {
        const Pacman& pacman { gameState.getPacMan() };
        
        return Entity::Direction::none;
    }
}