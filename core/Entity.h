#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <array>
#include <cmath>
#include <vector>

#include "Position.h"
#include "ColorData.h"

#include <cassert>
#include <algorithm>
#include <ranges>
#include <unordered_map>

class GameState;

class Entity
{
    //Direction enum must pair with directions pair array
public:
    enum class Direction { up, down, left, right, none };

protected:
    static constexpr std::array directions
    {
        Direction::up,
        Direction::down,
        Direction::left,
        Direction::right,
    };

    static constexpr std::array directionsOffset
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
    Direction m_facingDirection{ Direction::none };
    std::string m_color{ Color::RESET };

public:
    virtual ~Entity() = default;
    Entity() = default;
    Entity(SV name, char symbol, const Position& pos, SV color);

    const std::string& getName() const;
    char getSymbol() const;
    const std::string& getColor() const;

    Position getPosition() const;
    void setPosition(const Position& pos);

    Direction getDirection() const;
    void setDirection(Direction dir);

    static Direction getRandomDirection();
    static Direction getNonOppositeRandomDirection(Direction dir);
    static Direction getOppositeDirection(Direction dir);

    //Should be callable even without object
    static std::pair<int, int> getDirectionOffset(Direction dir);

    std::vector<Direction> getValidDirections(const GameState& gameState);
    Direction getBestDirection(const std::unordered_map<Direction, double>& directionDistance);

    void move(Direction dir);

    bool isAt(const Position& pos) const;
    bool isAt(int row, int col) const;
};