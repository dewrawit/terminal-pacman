#pragma once

#include <string>
#include <string_view>

#include "Entity.h"
#include "Position.h"
#include "AsciiData.h"

class Ghost : public Entity
{
    public:
    enum class GhostState { stalemate, chase, scatter, scared, dead };

    private:
    using SV = std::string_view;
    GhostState m_state{ GhostState::stalemate };
    Position m_target{};

    public:
    virtual ~Ghost() = default; //Plan to make gamestate store unique_ptr to Ghost
    Ghost() = default;
    Ghost(SV name, char symbol, const Position& pos)
        : Entity{ name, symbol, pos }
        , m_state{ GhostState::stalemate }
    { }

    GhostState getState() const { return m_state; }
    void setState(const GhostState& state) { m_state = state; }

    Position getTarget() const { return m_target; }
    virtual void setTarget(const Position& pos) { m_target = pos; }

    bool isScared() const { return m_state == GhostState::scared; }
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