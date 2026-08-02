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
#include <algorithm>
#include <ranges>

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
        for(int row {0}; row < board.getHeight(); ++row)
        {
            for(int col {0}; col < board.getLength(); ++col)
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

    const Pacman& getPacman() const { return m_pacman; }
    Pacman& getPacman() { return m_pacman; }

    const Ghost& ghostAt(const Position& pos) const
    {
        auto ghostIt { std::ranges::find_if(m_ghosts,
            [pos](const auto& ghostPtr) -> bool
            {
                return ghostPtr->getPosition() == pos;
            }
        )};

        if(ghostIt == m_ghosts.end())
        {
            assert(false && "No ghost at this position");
        }

        return **ghostIt;
    }
    Ghost& ghostAt(const Position& pos)
    {
        //Treat *this as const ref, then after calling the const ghostAt, drop the const
        return const_cast<Ghost&>(std::as_const(*this).ghostAt(pos));
    }
    void removePelletAt(const Position& pos)
    {
        std::erase_if(m_pellets,
            [pos](const Pellet& pellet) -> bool
            {
                return pellet.getPosition() == pos;
            }
        );
    }
    void makeAllGhostsScared()
    {
        for(auto& ghostPtr : m_ghosts)
        {
            ghostPtr->setState(Ghost::GhostState::scared);
        }
    }
    void updateGhostTimer()
    {
        //Handle Ghost Timer
        for(auto& ghostPtr : m_ghosts)
        {
            //There is no timer for dead state, ghost respawn when it's corpse reaches house
            if(ghostPtr->isDead())
            {
                ghostPtr->deactivateAllTimer();
                continue;
            }
            else
            {
                Ghost::GhostState currentGhostState { ghostPtr->getState() };
                Timer& selectedTimer { ghostPtr->getTimer(currentGhostState) };

                if(selectedTimer.isRunning())
                {
                    selectedTimer.decrement();
                }
                else
                {
                    selectedTimer.activateAndReset();
                } 
            }
        }    
    }
    void updateTileData()
    {
        //Update Tile info
        for(int row {0}; row < m_board.getHeight(); ++row)
        {
            for(int col {0}; col < m_board.getLength(); ++col)
            {
                Tile& tile = m_board.getTileAtPosition(row, col);

                //Wall cannot be overwritten
                if(tile.isWall())
                    continue;

                if(tile.isPellet() && 
                m_pacman.isAt(row, col))
                {
                    tile.setSymbol(AsciiData::PacmanSymbol);
                }
            }
        }
    }
    void update()
    {
        updateGhostTimer();
        updateTileData();
    }
};