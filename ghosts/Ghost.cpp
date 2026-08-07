#include "Ghost.h"

#include "../Entity.h"
#include "../Position.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../ColorData.h"
#include "../LevelInfo.h"
#include "../GameState.h"
#include "../Game.h"

#include <string_view>
#include <vector>
#include <cassert>
#include <ranges>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using SV = std::string_view;

Ghost::Ghost(SV name, char symbol, const Position& pos, SV color, const Timer& releaseTimer)
    : Entity{ name, symbol, pos, color }
    , m_state{ GhostState::stalemate }
    , m_releaseTimer{ releaseTimer }
{ }

Ghost::GhostState Ghost::getState() const
{
    return m_state;
}

Ghost::GhostState Ghost::getGhostStateFromTimer(const Timer& timer)
{
    switch(timer.getType())
    {
        case Timer::TimerTypes::chase: return Ghost::GhostState::chase; break;
        case Timer::TimerTypes::scatter: return Ghost::GhostState::scatter; break;
        case Timer::TimerTypes::scared: return Ghost::GhostState::scared; break;
        default: assert(false && "Invalid timer type");
    }
}

void Ghost::setState(const GhostState& state)
{
    m_state = state;
}

bool Ghost::isScared() const
{
    return m_state == GhostState::scared;
}

bool Ghost::isDead() const
{
    return m_state == GhostState::dead;
}

Position Ghost::getTarget() const
{
    return m_target;
}

void Ghost::setTarget(GameState&)
{
    return;
}

Timer& Ghost::getWaitTimer()
{
    return m_releaseTimer;
}

void Ghost::decrementWaitTimer(GameState& gameState)
{
    if(m_state != GhostState::stalemate)
        return;

    assert(m_releaseTimer.isRunning() && "Ghost wait timer is not running");

    m_releaseTimer.decrement();

    if(m_releaseTimer.timeout())
    {
        m_pos = LevelInfo::ghostSpawn;

        //After wait finish ghost state will be whatever global timer active
        setState(getGhostStateFromTimer(gameState.getActiveTimer()));
    }

    //debug
    //std::cout << m_name << " has state " << static_cast<int>(m_state) << std::endl;

}
void Ghost::moveTowardTarget(GameState& gameState)
{
    if(m_state == GhostState::stalemate)
        return;

    //Just finished waiting
    if(getWaitTimer().timeout() && getWaitTimer().isRunning())
    {
        m_pos = LevelInfo::ghostSpawn; //get out of the house
        getWaitTimer().deactivateAndReset();
        return;
    }

    while(m_speedCredits >= m_speedToMove)
    {
        m_speedCredits -= m_speedToMove;
        std::vector<Direction> validDirections{ getValidDirections(gameState) };

        //Can go many ways, pick the best one.
        std::unordered_map<Direction,double> directionDistance {};

        for(const auto& direction : validDirections)
        {
            Position newPosition { m_pos + getDirectionOffset(direction) };
            directionDistance[direction] = m_target.distance(newPosition);
        }

        Direction bestDirection { getBestDirection(directionDistance) };

        if(m_facingDirection == Direction::none)
        {
            m_facingDirection = bestDirection;
            move(bestDirection);
        }
        else
        {
            //ignore opposite direction
            directionDistance.erase(getOppositeDirection(m_facingDirection));

            //This should also handle one way path case
            //(since thats the only path it can go so it has the best distance in valid directions)
            bestDirection = getBestDirection(directionDistance);
            m_facingDirection = bestDirection;
            move(bestDirection);
        }

        if(isDead() && m_pos == LevelInfo::ghostSpawn) //back home
        {
            m_state = getGhostStateFromTimer(gameState.getActiveTimer());
        }
    }
}
void Ghost::setSpeed()
{
    switch(m_state)
    {
        case GhostState::stalemate: m_speedCredits = 0; break;
        case GhostState::scared: m_speedCredits += m_speedToMove / 2; break;
        case GhostState::dead: m_speedCredits += m_speedToMove * 3; break;
        default: m_speedCredits += m_speedToMove; break;
    }
}
void Ghost::resetSpeed()
{
    m_speedCredits = 0;
}
void Ghost::flipDirection()
{
    if(m_facingDirection == Direction::none)
    {
        return;
    }
    m_facingDirection = getOppositeDirection(m_facingDirection);
}
SV Ghost::ghostStateToStr(GhostState ghostState)
{
    switch(ghostState)
    {
        case GhostState::chase: return "Chase";
        case GhostState::dead: return "Dead";
        case GhostState::scared: return "Scared";
        case GhostState::scatter: return "Scatter";
        case GhostState::stalemate: return "Stalemate";
        default: assert(false && "Detect invalid state in ghostStateToStr");
    }
}