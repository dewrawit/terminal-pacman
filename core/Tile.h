#pragma once

#include "Position.h"
#include "AsciiData.h"

class Tile
{
    private:
    bool m_walkable{};
    Position m_position{};
    bool m_ghostDoor{false};


    public:
    Tile() = default;
    Tile(bool walkable, const Position& pos, bool ghostDoor = false) 
        : m_walkable{ walkable }
        , m_position{ pos }
        , m_ghostDoor{ ghostDoor }
    { }

    Position getPosition() const { return m_position; }
    bool isWalkable() const { return m_walkable; }
    bool isWall() const { return !isWalkable(); }
    bool isGhostDoor() const { 
        assert(isWall() && "Accidental Assign ghost wall to not be a wall");
        return m_ghostDoor; 
    }
};