#pragma once

#include <string>
#include <string_view>
#include "Entity.h"

class Ghost
{
    public:
    enum class GhostState { stalemate, chase, scatter, scared, dead };

    private:
    GhostState m_state{ GhostState::stalemate };

    public:
    virtual ~Ghost() = default; //Plan to make gamestate store unique_ptr to Ghost
    Ghost() = default;

    GhostState getState() const { return m_state; }
    void setState(GhostState state) { m_state = state; }
};