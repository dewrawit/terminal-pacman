#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include <vector>
#include <memory>
#include <cassert>

class GameState
{
    private:
    Board m_board{};
    Pacman m_pacman{};
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};

    public:
    
    //Game state must read board data to create entites at correct position
    GameState(const Board& board) 
    {
        for(auto row {0uz}; row < board.getHeight(); ++row)
        {
            for(auto col {0uz}; col < board.getLength(); ++col)
            {
                switch(board.getTileAtPosition(row,col).getSymbol())
                {
                    case 'P':
                    case 'B':
                    case 'N':
                    case 'I':
                    case 'C':
                    case '.':
                    case 'o':
                    case '#':
                    default: assert(false && "Board map contains invalid symbol\n");
                }
            }
        }
    }
};