#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <array>
#include "Position.h"

class Entity
{
    //Direction enum must pair with directions pair array
    public:
    enum class Direction { up, down, left, right, none };

    protected:
    static constexpr std::array directions
    {
        std::pair{-1,0}, //Up
        std::pair{1,0}, //Down
        std::pair{0,-1}, //Left
        std::pair{0,1}, //Right
    };

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
    void setDirection(Direction dir) { m_dir = dir; } 

    //Should be callable even without object
    static std::pair<int,int> getDirectionOffset(Direction dir)
    { 
        return directions[static_cast<std::size_t>(dir)];
    } 

    void move(Direction dir) 
    {
        m_pos = m_pos + getDirectionOffset(dir);
    }
};