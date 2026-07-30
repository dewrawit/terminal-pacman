#pragma once

#include "Position.h"

class Tile
{
    private:
    char m_symbol{' '};
    Position m_position{};

    public:
    Tile() = default;
    Tile(char symbol, const Position& pos) 
        : m_symbol{ symbol }
        , m_position{ pos }
    { }

    char getSymbol() const { return m_symbol; }
    Position getPosition() const { return m_position; }
    bool isOccupied() const { return m_symbol != ' '; }
    bool isEmpty() const { return m_symbol == ' '; }
};