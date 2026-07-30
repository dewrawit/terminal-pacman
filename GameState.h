#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include <vector>
#include <memory>

class GameState
{
    private:
    Board m_board{};
    Pacman m_pacman{};
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};

    public:
    
    GameState(const Board& board)
    {
       
    }
};