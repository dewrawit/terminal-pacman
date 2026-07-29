#pragma once

#include <string>
#include "Entity.h"

struct Position;

class Pacman : public Entity
{
    private:
    bool m_alive { true };

    public:
    Pacman(const Position& pos) 
        : Entity{"Pac-man",'P',pos}
        , m_alive{ true } 
    { }

    bool isAlive() const { return m_alive; }
    bool isDead() const { return !m_alive; }
};