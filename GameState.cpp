#include "GameState.h"

#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <print>

#include "LevelInfo.h"
#include "Position.h"
#include "AsciiData.h"

GameState::GameState(const AsciiMap& map) : m_board{ map }
{
    for(int row {0}; row < m_board.getHeight(); ++row)
    {
        for(int col {0}; col < m_board.getLength(); ++col)
        {
            Position currentPosition = Position{ row, col };
            switch(map[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)])
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

const Board& GameState::getBoard() const
{
    return m_board;
}

Board& GameState::getBoard()
{
    return m_board;
}

const Pacman& GameState::getPacman() const
{
    return m_pacman;
}

Pacman& GameState::getPacman()
{
    return m_pacman;
}

const Ghost& GameState::ghostAt(const Position& pos) const
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

Ghost& GameState::ghostAt(const Position& pos)
{
    //Treat *this as const ref, then after calling the const ghostAt, drop the const
    return const_cast<Ghost&>(std::as_const(*this).ghostAt(pos));
}
bool GameState::containsGhostAt(const Position& pos) const
{
    for(const auto& ghostPtr : m_ghosts)
    {
        if(ghostPtr->getPosition() == pos)
        {
            return true;
        }
    }
    return false;
}
const Pellet& GameState::pelletAt(const Position& pos) const
{
    assert(containsPelletAt(pos) && "No pellet at this position");

    auto it { std::ranges::find_if(m_pellets, [pos](const Pellet& pellet) -> bool
        {
            return pellet.getPosition() == pos;
        })};

    if(it != m_pellets.end())
    {
        return *it;
    }

    assert(false && "No pellet at this Position 2");
}
void GameState::removePelletAt(const Position& pos)
{
    std::erase_if(m_pellets,
        [pos](const Pellet& pellet) -> bool
        {
            return pellet.getPosition() == pos;
        }
    );
}
bool GameState::containsPelletAt(const Position& pos) const
{
    for(const auto& pellet : m_pellets)
    {
        if(pellet.getPosition() == pos)
        {
            return true;
        }
    }
    return false;
}

void GameState::makeAllGhostsScared()
{
    for(auto& ghostPtr : m_ghosts)
    {
        ghostPtr->setState(Ghost::GhostState::scared);
    }
}

void GameState::updateGhostTimer()
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

void GameState::updateTileData()
{
    //Update Tile info
    // for(int row {0}; row < m_board.getHeight(); ++row)
    // {
    //     for(int col {0}; col < m_board.getLength(); ++col)
    //     {
    //         Tile& tile = m_board.getTileAtPosition(row, col);

    //         //Wall cannot be overwritten
    //         if(tile.isWall())
    //             continue;

    //         if(tile.isWalkable() &&
    //         m_pacman.isAt(row, col))
    //         {
    //             tile.setSymbol(AsciiData::PacmanSymbol);
    //         }
    //     }
    // }
}

void GameState::update()
{
    updateGhostTimer();
    updateTileData();
}
char GameState::getGameObjectSymbolAt(const Position& pos)
{
    //Check Pellet
    auto pelletIt { std::ranges::find_if(m_pellets, [pos](const Pellet& pellet) -> bool
        {
            return pellet.getPosition() == pos;
        })};

    if( pelletIt != m_pellets.end() )
    {
        return pelletIt->isSuperPellet() ? 
        AsciiData::SuperPelletSymbol : AsciiData::NormalPelletSymbol;
    }
        
    //Check Ghost
    auto ghostIt { std::ranges::find_if(m_ghosts, [pos](const auto& ghostPtr) -> bool
        {
            return ghostPtr->getPosition() == pos;
        })};

    if(ghostIt != m_ghosts.end())
    {
        return (*ghostIt)->getSymbol();
    }

    //Check Pacman
    if(m_pacman.getPosition() == pos)
    {
        return m_pacman.getSymbol();
    }

    return ' ';
}
char GameState::getGameObjectSymbolAt(int row, int col)
{
    return getGameObjectSymbolAt(Position{row, col});
}
void GameState::renderBoard()
{
    //Seperator each turn to not clutter terminal
    for(int i {0}; i < 20; ++i)
    {
        std::println();
    }

    for(int row {0}; row < m_board.getHeight(); ++row)
    {
        for(int col {0}; col < m_board.getLength(); ++col)
        {
            if(m_board.getTileAtPosition(row, col).isWall())
            {
                std::print("{}",AsciiData::WallSymbol);
            }
            else
            {
                std::print("{}",getGameObjectSymbolAt(row, col));
            }
        }
        std::println();
    }
}
bool GameState::win()
{
    return m_pellets.empty();
}
bool GameState::lose()
{
    return m_lives <= 0;
}