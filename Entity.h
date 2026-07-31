#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <array>
#include "Position.h"

class Entity
{
    protected:
    static constexpr std::array directions
    {
        std::pair{0,-1}, //Up
        std::pair{0,1}, //Down
        std::pair{-1,0}, //Left
        std::pair{1,0}, //Right
    };

    public:
    enum class Direction { up, down, left, right, none };

    private:
    using SV = std::string_view;

    std::string m_name{};
    char m_symbol{};
    Position m_pos{};
    Direction m_dir{Direction::none};

    public:
    virtual ~Entity() = default;
    Entity() = default;
    Entity(SV name, char symbol, const Position& pos)
        : m_name{ name }
        , m_symbol{ symbol }
        , m_pos{ pos }
    { }

    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }

    Position getPosition() const { return m_pos; }
    void setPosition(const Position& pos) { m_pos = pos; }
    
    Direction getDirection() const { return m_dir; }
    void setDirection(const Direction& dir) { m_dir = dir; } 
};