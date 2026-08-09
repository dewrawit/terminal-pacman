#pragma once

#include <string>
#include "Entity.h"
#include "AsciiData.h"
#include "ColorData.h"

struct Position;

class Pacman : public Entity
{
    private:
    bool m_alive { true };

    public:
    Pacman() = default;
    Pacman(const Position& pos) 
        : Entity{"Pac-man",AsciiData::PacmanSymbol,pos,Color::YELLOW}
        , m_alive{ true } 
    { }

    bool isAlive() const { return m_alive; }
    bool isDead() const { return !m_alive; }
};