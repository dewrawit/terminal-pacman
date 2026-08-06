#pragma once

#include <string>
#include <string_view>

#include "../Entity.h"
#include "../Position.h"
#include "../Timer.h"

class GameState;

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
    Ghost(SV name, char symbol, const Position& pos, SV color, const Timer& releaseTimer);

    GhostState getState() const;
    static GhostState getGhostStateFromTimer(const Timer& timer);
    void setState(const GhostState& state);
    bool isScared() const;
    bool isDead() const;

    Position getTarget() const;
    virtual void setTarget(GameState&);
    Timer& getWaitTimer();
    void decrementWaitTimer(GameState& gameState);
    void moveTowardTarget(GameState& gameState);
};