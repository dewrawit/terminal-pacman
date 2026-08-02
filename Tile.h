#pragma once

#include "Position.h"
#include "AsciiData.h"

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
    void setSymbol(char c) { m_symbol = c; }
    Position getPosition() const { return m_position; }
    bool isOccupied() const { return m_symbol != ' '; }
    bool isEmpty() const { return m_symbol == ' '; }
    bool isWalkable() const { return m_symbol != AsciiData::WallSymbol; }
    bool isWall() const { return m_symbol == AsciiData::WallSymbol; }
    bool isNormalPellet() const { return m_symbol == AsciiData::NormalPelletSymbol; }
    bool isSuperPellet() const { return m_symbol == AsciiData::SuperPelletSymbol; }
    bool isPellet() const { return isNormalPellet() || isSuperPellet(); }
    bool isGhost() const {
        switch(m_symbol)
        {
            case AsciiData::BlinkySymbol:
            case AsciiData::ClydeSymbol:
            case AsciiData::InkySymbol:
            case AsciiData::PinkySymbol:
                return true;
            default:
                return false;
        }
    }
    bool isPacman() const { return m_symbol == AsciiData::PacmanSymbol; }
};