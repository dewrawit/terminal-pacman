#include "GameState.h"

#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <print>

#include "ghosts/AllGhosts.h"
#include "LevelInfo.h"
#include "Position.h"
#include "AsciiData.h"
#include "ColorData.h"
#include "Pacman.h"

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
                    m_spawnPoints[Character::pacman] = currentPosition;
                    break;
                case AsciiData::BlinkySymbol:
                    m_ghosts.emplace_back(std::make_unique<Blinky>(currentPosition));
                    m_spawnPoints[Character::blinky] = currentPosition;
                    break;
                case AsciiData::PinkySymbol:
                    m_ghosts.emplace_back(std::make_unique<Pinky>(currentPosition));
                    m_spawnPoints[Character::pinky] = currentPosition;
                    break;
                case AsciiData::InkySymbol:
                    m_ghosts.emplace_back(std::make_unique<Inky>(currentPosition));
                    m_spawnPoints[Character::inky] = currentPosition;
                    break;
                case AsciiData::ClydeSymbol:
                    m_ghosts.emplace_back(std::make_unique<Clyde>(currentPosition));
                    m_spawnPoints[Character::clyde] = currentPosition;
                    break;
                case AsciiData::NormalPelletSymbol:
                    m_pellets.emplace_back(currentPosition, Pellet::Type::normal);
                    break;
                case AsciiData::SuperPelletSymbol:
                    m_pellets.emplace_back(currentPosition, Pellet::Type::super);
                    break;
                //GameState do not need to store these info (Tile can check wall)
                case AsciiData::WallSymbol: 
                case AsciiData::GhostDoorSymbol:
                case ' ':
                    break;

                default: assert(false && "Board map contains invalid symbol");
            }
        }
    }

    //Timers
    m_globalTimers[Timer::TimerTypes::chase] = Timer("Chase", 20, Timer::TimerTypes::chase);
    m_globalTimers[Timer::TimerTypes::scatter] = Timer("Scatter", 10, Timer::TimerTypes::scatter);
    m_globalTimers[Timer::TimerTypes::scared] = Timer("Scared", 10, Timer::TimerTypes::scared);

    //Each ghost has it's own stalemate timer
    //m_globalTimers[Timer::TimerTypes::stalemate] = Timer(40, Timer::TimerTypes::stalemate);
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

std::vector<std::unique_ptr<Ghost>>& GameState::getGhosts()
{
    return m_ghosts;
}

const std::vector<std::unique_ptr<Ghost>>& GameState::getGhosts() const
{
    return m_ghosts;
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
bool GameState::oneTimerActive()
{
    int activeTimers{ 0 };
    for(const auto& timer : m_globalTimers)
    {
        if(timer.isRunning())
        {
            ++activeTimers;
        }
    }
    return activeTimers == 1;
}
Timer& GameState::getActiveTimer()
{
    assert(oneTimerActive() && "Detect multiple or no active timers in getActiveTimer()");

    for(auto& timer : m_globalTimers)
    {
        if(timer.isRunning())
        {
            return timer;
        }
    }

    assert(false && "This is here so compiler don't complain no return type");
}
void GameState::makeAllGhosts(Ghost::GhostState state)
{
    for(auto& ghostPtr : m_ghosts)
    {
        ghostPtr->setState(state);
    }
}
void GameState::applyGhostCurrentTimerEffect()
{
    assert(oneTimerActive() && "Detect multiple active timers in applyGhostTimerEffect()");

    const Timer& activeTimer { getActiveTimer() };

    Ghost::GhostState stateToActive{ Ghost::getGhostStateFromTimer(activeTimer)};

    makeAllGhosts(stateToActive);

    //Some ghost might still have thier waiting timer active
    for(auto& ghostPtr : m_ghosts)
    {
        if(!ghostPtr->getWaitTimer().timeout() && ghostPtr->getWaitTimer().isRunning())
        {
            ghostPtr->setState(Ghost::GhostState::stalemate);
        }
    }
}
void GameState::updateTimer()
{
    assert(oneTimerActive() && "Detect multiple active timers in updateTimer()");

    Timer& activeTimer { getActiveTimer() };
    activeTimer.decrement();

    //Change active timer if the last one timeout
    if(activeTimer.timeout())
    {
        switch(activeTimer.getType())
        {
            case Timer::TimerTypes::chase: 
                activateTimerState(Timer::TimerTypes::scatter);
                break;
            case Timer::TimerTypes::scatter: 
                activateTimerState(Timer::TimerTypes::chase);
                break;
            case Timer::TimerTypes::scared: 
                activateTimerState(Timer::TimerTypes::chase);
                break;
            // case Timer::TimerTypes::stalemate: 
            //     activateTimerState(Timer::TimerTypes::scatter);
            //     break;
            default: assert(false && "Invalid TimerType in updateTimer()"); break;
        }
    }
}
void GameState::update()
{
    updateTimer();
    applyGhostCurrentTimerEffect();
    for(auto& ghostPtr : m_ghosts)
    {
        ghostPtr->decrementWaitTimer(*this);
    }
}
char GameState::getGameObjectSymbolAt(const Position& pos)
{
    //Priority: should check for ghost first (if ghost overlap with pellet it should print ghost)

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

    std::println("Lives: {}", getLives());

    //DEBUG
    std::println("Active: {}", getActiveTimer().getName());

    for(int row {0}; row < m_board.getHeight(); ++row)
    {
        for(int col {0}; col < m_board.getLength(); ++col)
        {
            if(m_board.getTileAtPosition(row, col).isWall())
            {
                if(m_board.getTileAtPosition(row, col).isGhostDoor())
                {
                    std::print("{}={}", Color::WALLBLUE, Color::RESET);
                }
                else
                {
                    std::print("{}█{}", Color::WALLBLUE, Color::RESET);
                }
            }
            else
            {
                //Either pacman, ghost, pellet or empty
                char symbol { getGameObjectSymbolAt(row, col) };
                std::string color{Color::RESET};

                //Check which Color
                switch(symbol)
                {
                    case AsciiData::NormalPelletSymbol:
                    case AsciiData::SuperPelletSymbol:
                    case AsciiData::EmptySymbol:
                        break;

                    case AsciiData::PacmanSymbol: 
                        color = m_pacman.getColor(); 
                        break;

                    default: //Ghost
                        if(ghostAt(Position{row, col}).isScared())
                        {
                            color = Color::SCAREDBLUE;
                        }
                        else
                        {
                            color = ghostAt(Position{row, col}).getColor();
                        } 
                        break;
                }
                std::print("{}{}{}",color,symbol,Color::RESET);
            }
        }
        std::println();
    }
}
bool GameState::win() const
{
    return m_pellets.empty();
}
bool GameState::lose() const
{
    return m_lives <= 0;
}
Timer& GameState::getTimer(Timer::TimerTypes type)
{
    return m_globalTimers[type];
}
void GameState::activateTimerState(Timer::TimerTypes type)
{
    //Deactivate other timer (since ghost can only have one state at a time)
    for(auto& timer : m_globalTimers)
    {
        timer.deactivateAndReset();
    }

    m_globalTimers[type].activateAndReset();
}
void GameState::startGhostsWaitTimer()
{
    for(auto& ghostPtr : m_ghosts)
    {
        ghostPtr->getWaitTimer().activateAndReset();
    }
}
int GameState::getLives() const
{
    return m_lives;
}
void GameState::loseALife()
{
    --m_lives;
}
void GameState::respawn()
{
    m_pacman.setPosition(m_spawnPoints[Character::pacman]);

    for(auto& ghostPtr : m_ghosts)
    {
        switch(ghostPtr->getSymbol())
        {
            case AsciiData::BlinkySymbol:
                ghostPtr->setPosition(m_spawnPoints[Character::blinky]);
                break;
            case AsciiData::PinkySymbol:
                ghostPtr->setPosition(m_spawnPoints[Character::pinky]);
                break;  
            case AsciiData::InkySymbol:
                ghostPtr->setPosition(m_spawnPoints[Character::inky]);
                break;
            case AsciiData::ClydeSymbol:
                ghostPtr->setPosition(m_spawnPoints[Character::clyde]);
                break;
        }

        //Gotta restart ghost stalemate timer too
        ghostPtr->setState(Ghost::GhostState::stalemate);
        ghostPtr->getWaitTimer().activateAndReset();
    }
}
void GameState::retargetGhosts()
{
    for(auto& ghostPtr : m_ghosts)
    {
        ghostPtr->setTarget(*this);
    }
}
const Blinky& GameState::getBlinky() const
{
    for(auto& ghostPtr : m_ghosts)
    {
        if(ghostPtr->getSymbol() == AsciiData::BlinkySymbol)
        {
            return dynamic_cast<Blinky&>(*ghostPtr);
        }
    }
    assert(false && "Blinky not found");
}
void GameState::moveGhosts()
{
    for(auto& ghostPtr : m_ghosts)
    {
        ghostPtr->moveTowardTarget(*this);
    }
}