#include "Entity.h"

#include "Position.h"
#include "ColorData.h"
#include "LevelInfo.h"
#include "GameState.h"
#include "Game.h"
#include "Random.h" //Using learncpp library

Entity::Entity(SV name, char symbol, const Position& pos, SV color)
    : m_name{ name }
    , m_symbol{ symbol }
    , m_pos{ pos }
    , m_color{ color }
{
}

const std::string& Entity::getName() const
{
    return m_name;
}

char Entity::getSymbol() const
{
    return m_symbol;
}

const std::string& Entity::getColor() const
{
    return m_color;
}

Position Entity::getPosition() const
{
    return m_pos;
}

void Entity::setPosition(const Position& pos)
{
    m_pos = pos;
}

Entity::Direction Entity::getDirection() const
{
    return m_facingDirection;
}

void Entity::setDirection(Direction dir)
{
    m_facingDirection = dir;
}

Entity::Direction Entity::getRandomDirection()
{
    Direction dir{ static_cast<Direction>(Random::get<int>(0, 3)) };

    assert(dir != Direction::none && "Random direction shouldn't gave None");

    return dir;
}

Entity::Direction Entity::getNonOppositeRandomDirection(Direction dir)
{
    Direction opposite = getOppositeDirection(dir);
    while (true)
    {
        Direction randomDir{ getRandomDirection() };
        if (randomDir != opposite)
        {
            return randomDir;
        }
    }
}

Entity::Direction Entity::getOppositeDirection(Direction dir)
{
    switch (dir)
    {
    case Direction::up: return Direction::down;
    case Direction::down: return Direction::up;
    case Direction::left: return Direction::right;
    case Direction::right: return Direction::left;
    default: assert(false && "Cannot get opposite direction of None Direction");
    }
}

std::pair<int, int> Entity::getDirectionOffset(Direction dir)
{
    assert(dir != Direction::none && "Cannot get opposite direction of None");
    return directionsOffset[static_cast<std::size_t>(dir)];
}

std::vector<Entity::Direction> Entity::getValidDirections(const GameState& gameState)
{
    std::vector<Direction> validDirections{};

    for (const auto& direction : directions)
    {
        if(Game::validDirection(*this, direction, gameState))
        {
            validDirections.push_back(direction);
        }
    }

    assert(validDirections.size() >= 2 && "Expect >= 2 direction (Map shouldn't have dead ends)");

    return validDirections;
}

Entity::Direction Entity::getBestDirection(const std::unordered_map<Direction, double>& directionDistance)
{
    assert(!directionDistance.empty() && "Cannot get best direction on empty hashmap");

    auto minIt{ std::ranges::min_element(directionDistance,
    [](const auto& left, const auto& right) -> bool
    {
        return left.second < right.second;
    }
    ) };

    return minIt->first;
}

void Entity::move(Direction dir)
{
    //DEBUG
    //std::cout << m_pos << std::endl;

    m_pos = m_pos + getDirectionOffset(dir);

    //(column in bound is 0-27), length = 28
    //so out of bound column is -1 or 28

    //Side Tunnel check
    if (m_pos.outOfBounds())
    {
        //Teleport to other side (same row, opposite column)
        int newColumn{};

        if (m_pos.col < LevelInfo::mapLength)
        {
            newColumn = LevelInfo::mapLength + m_pos.col;
        }
        else if (m_pos.col >= LevelInfo::mapLength)
        {
            newColumn = m_pos.col - LevelInfo::mapLength;
        }

        m_pos = Position{ m_pos.row, newColumn };

        //DEBUG
        //std::cout << m_pos << std::endl;
    }

    m_facingDirection = dir;
}

bool Entity::isAt(const Position& pos) const
{
    return m_pos == pos;
}

bool Entity::isAt(int row, int col) const
{
    return m_pos == Position{ row, col };
}