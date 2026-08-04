#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <array>
#include <cmath>
#include "Position.h"
#include "ColorData.h"
#include "LevelInfo.h"
#include "Random.h" //Using learncpp library

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

    protected:
    using SV = std::string_view;

    std::string m_name{};
    char m_symbol{};
    Position m_pos{};
    Direction m_dir{Direction::none};
    std::string m_color {Color::RESET};

    public:
    virtual ~Entity() = default;
    Entity() = default;
    Entity(SV name, char symbol, const Position& pos, SV color)
        : m_name{ name }
        , m_symbol{ symbol }
        , m_pos{ pos }
        , m_color{ color }
    { }

    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    const std::string& getColor() const { return m_color; }

    Position getPosition() const { return m_pos; }
    void setPosition(const Position& pos) { m_pos = pos; }
    
    Direction getDirection() const { return m_dir; }
    void setDirection(Direction dir) { m_dir = dir; }

    static Direction getRandomDirection()
    {
        return static_cast<Direction>(Random::get<int>(0,3));
    }

    //Should be callable even without object
    static std::pair<int,int> getDirectionOffset(Direction dir)
    { 
        return directions[static_cast<std::size_t>(dir)];
    } 

    void move(Direction dir) 
    {
        //DEBUG
        //std::cout << m_pos << std::endl;

        m_pos = m_pos + getDirectionOffset(dir);

        //(column in bound is 0-27), length = 28
        //so out of bound column is -1 or 28

        //Side Tunnel check
        if(m_pos.outOfBounds())
        {
            //Teleport to other side (same row, opposite column)
            int newColumn {};

            if(m_pos.col < LevelInfo::mapLength)
            {
                newColumn = LevelInfo::mapLength + m_pos.col;
            }
            else if(m_pos.col >= LevelInfo::mapLength)
            {
                newColumn = m_pos.col - LevelInfo::mapLength;
            }

            m_pos = Position{ m_pos.row, newColumn };

            //DEBUG
            //std::cout << m_pos << std::endl;
        }
    }

    bool isAt(const Position& pos)
    {
        return m_pos == pos;
    }
    bool isAt(int row, int col)
    {
        return m_pos == Position{ row, col };
    }
};