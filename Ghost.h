#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "Entity.h"
#include "Position.h"
#include "AsciiData.h"
#include "Timer.h"

class Ghost : public Entity
{
    public:
    enum class GhostState { stalemate, chase, scatter, scared, dead };
    enum TimerTypes { stalemate, chase, scatter, scared, maxTimerTypes };
    using GhostTimerArray = 
    std::array<Timer,TimerTypes::maxTimerTypes>;

    private:
    using SV = std::string_view;

    GhostState m_state{ GhostState::stalemate };
    Position m_target{};
    GhostTimerArray m_timers{};

    public:
    virtual ~Ghost() = default; //Plan to make gamestate store unique_ptr to Ghost
    Ghost() = default;
    Ghost(SV name, char symbol, const Position& pos)
        : Entity{ name, symbol, pos }
        , m_state{ GhostState::stalemate }
    { 
        m_timers[TimerTypes::stalemate] = Timer(5);
        m_timers[TimerTypes::chase] = Timer(20);
        m_timers[TimerTypes::scatter] = Timer(10);
        m_timers[TimerTypes::scared] = Timer(10);
    }

    GhostState getState() const { return m_state; }
    void setState(const GhostState& state) { m_state = state; }
    bool isScared() const { return m_state == GhostState::scared; }

    Position getTarget() const { return m_target; }
    virtual void setTarget(const Position& pos) { m_target = pos; }
    
    Timer& getTimer(TimerTypes type)
    {
        return m_timers[type];
    }
    Timer& getTimer(GhostState state)
    {
        switch(state)
        {
            case GhostState::chase: return getTimer(TimerTypes::chase);
            case GhostState::scared: return getTimer(TimerTypes::scared);
            case GhostState::scatter: return getTimer(TimerTypes::scatter);
            case GhostState::stalemate: return getTimer(TimerTypes::stalemate);
            default: assert(false && "Cannot get timer of this ghost state.");
        }
    }

    void activateTimerState(TimerTypes type)
    {
        //Deactivate other timer (since ghost can only have one state at a time)
        for(auto& timer : m_timers)
        {
            timer.deactivateAndReset();
        }

        m_timers[type].activateAndReset();
    }
};

class Blinky : public Ghost
{
    public:
    Blinky(const Position& pos) 
        : Ghost{ "Blinky", AsciiData::BlinkySymbol, pos }
    { }
};

class Pinky : public Ghost
{
    public:
    Pinky(const Position& pos) 
        : Ghost{ "Pinky", AsciiData::PinkySymbol, pos } //'P' collides with Pac-man
    { }
};

class Inky : public Ghost
{
    public:
    Inky(const Position& pos) 
        : Ghost{ "Inky", AsciiData::InkySymbol, pos }
    { }
};

class Clyde : public Ghost
{
    public:
    Clyde(const Position& pos) 
        : Ghost{ "Clyde", AsciiData::ClydeSymbol, pos }
    { }
};