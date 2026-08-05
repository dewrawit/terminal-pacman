#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "../Entity.h"
#include "../Position.h"
#include "../AsciiData.h"
#include "../Timer.h"
#include "../ColorData.h"
#include "../LevelInfo.h"

class Ghost : public Entity
{
    public:
    enum class GhostState { stalemate, chase, scatter, scared, dead };

    protected:
    using SV = std::string_view;

    GhostState m_state{ GhostState::stalemate };
    Position m_target{};
    Timer m_releaseTimer{};

    public:
    virtual ~Ghost() = default; //Plan to make gamestate store unique_ptr to Ghost
    Ghost() = default;
    Ghost(SV name, char symbol, const Position& pos, SV color, const Timer& releaseTimer)
        : Entity{ name, symbol, pos, color }
        , m_state{ GhostState::stalemate }
        , m_releaseTimer{ releaseTimer }
    { }

    GhostState getState() const { return m_state; }
    void setState(const GhostState& state) { m_state = state; }
    bool isScared() const { return m_state == GhostState::scared; }
    bool isDead() const { return m_state == GhostState::dead; }

    Position getTarget() const { return m_target; }
    virtual void setTarget(GameState&) { return; }
    Timer& getWaitTimer() { return m_releaseTimer; }
    void decrementWaitTimer()
    {
        if(m_state != GhostState::stalemate)
            return;

        assert(m_releaseTimer.isRunning() && "Ghost wait timer is not running");

        m_releaseTimer.decrement();

        if(m_releaseTimer.timeout())
        {
            m_pos = Position{ LevelInfo::ghostSpawnRow, LevelInfo::ghostSpawnCol };
            setState(GhostState::scatter);
        }
    }   
};