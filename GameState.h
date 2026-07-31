#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Pellet.h"
#include "Position.h"
#include "AsciiData.h"
#include <vector>
#include <memory>
#include <cassert>

class GameState
{
    private:
    Board m_board{};
    Pacman m_pacman{};
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};
    std::vector<Pellet> m_pellets{};

    public:
    
    //Game state must read board data to create entites at correct position
    GameState(const Board& board) : m_board{ board }
    {
        for(auto row {0uz}; row < board.getHeight(); ++row)
        {
            for(auto col {0uz}; col < board.getLength(); ++col)
            {
                Position currentPosition = Position{ row, col };
                switch(board.getTileAtPosition(row,col).getSymbol())
                {
                    case AsciiData::PacmanSymbol:
                        m_pacman = Pacman{currentPosition};
                        break;
                    case AsciiData::BlinkySymbol:
                        m_ghosts.push_back(std::make_unique<Blinky>(currentPosition));
                        break;
                    case AsciiData::PinkySymbol:
                        m_ghosts.push_back(std::make_unique<Pinky>(currentPosition));
                        break;
                    case AsciiData::InkySymbol:
                        m_ghosts.push_back(std::make_unique<Inky>(currentPosition));
                        break;
                    case AsciiData::ClydeSymbol:
                        m_ghosts.push_back(std::make_unique<Clyde>(currentPosition));
                        break;
                    case AsciiData::NormalPelletSymbol:
                        m_pellets.emplace_back(currentPosition, Pellet::Type::normal);
                        break;
                    case AsciiData::SuperPelletSymbol:
                        m_pellets.emplace_back(currentPosition, Pellet::Type::super);
                        break;
                    case AsciiData::WallSymbol:
                        break; //GameState do not need to store wall info (Tile can check wall)
                    case ' ':
                        break;

                    default: assert(false && "Board map contains invalid symbol");
                }
            }
        }
    }
    const Board& getBoard() const { return m_board; }
    Board& getBoard() { return m_board; }

    const Pacman& getPacMan() const { return m_pacman; }
    Pacman& getPacman() { return m_pacman; }
};