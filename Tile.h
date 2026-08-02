#pragma once

#include "Position.h"
#include "AsciiData.h"

class Tile
{
    private:
    bool m_walkable{};
    Position m_position{};

    public:
    Tile() = default;
    Tile(bool walkable, const Position& pos) 
        : m_walkable{ walkable }
        , m_position{ pos }
    { }

    Position getPosition() const { return m_position; }
    bool isWalkable() const { return m_walkable; }
    bool isWall() const { return !isWalkable(); }
};