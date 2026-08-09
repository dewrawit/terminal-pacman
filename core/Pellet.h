#pragma once

#include "AsciiData.h"
#include "Position.h"

class Pellet
{
    public:
    enum class Type { normal, super };

    private:
    Type m_type{Type::normal};
    char m_symbol{AsciiData::NormalPelletSymbol};
    Position m_position{};

    public:
    Pellet() = default;
    Pellet(const Position& position, Type type = Type::normal)
        : m_type{ type }
        , m_symbol{ isNormalPellet() ? AsciiData::NormalPelletSymbol : AsciiData::SuperPelletSymbol}
        , m_position{ position }
    { }
    char getSymbol() const { return m_symbol; }
    Type getType() const { return m_type; }
    Position getPosition() const { return m_position; }
    bool isNormalPellet() const { return m_type == Type::normal; }
    bool isSuperPellet() const { return m_type == Type::super; }


};