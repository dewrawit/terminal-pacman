#pragma once

#include <string>
#include <string_view>
#include "Position.h"

class Entity
{
    public:
    enum class Direction { up, down, left, right, none };

    private:
    using SV = std::string_view;

    std::string m_name{};
    char m_symbol{};
    Position m_pos{};
    Direction m_dir{};

    public:
    virtual ~Entity() = default;
    Entity(SV name, char symbol, Position pos)
        : m_name{ name }
        , m_symbol{ symbol }
        , m_pos{ pos }
    { }

    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    Position getPosition() const { return m_pos; }
    Direction getDirection() const { return m_dir; }
};