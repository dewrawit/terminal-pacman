#include "Ghost.h"

#include "../Entity.h"
#include "../Position.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../ColorData.h"
#include "../LevelInfo.h"
#include "../GameState.h"

#include <string_view>

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
        //m_pos = Position{ LevelInfo::ghostSpawnRow, LevelInfo::ghostSpawnCol };
        m_pos = LevelInfo::ghostSpawn;

        //After wait finish ghost state will be whatever global timer active
        setState(getGhostStateFromTimer(gameState.getActiveTimer()));
    }
}