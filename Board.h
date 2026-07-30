#pragma once

#include "Position.h"
#include "LevelInfo.h"
#include "Tile.h"
#include <array>
#include <print>

class Board
{
    public:
    using GameMap = std::array<std::array<Tile,LevelInfo::mapLength>,LevelInfo::mapHeight>;

    private:
    GameMap levelMap {};

    public:
    Board() = default;

    template <std::size_t Height>
    Board(const std::array<std::string_view,Height>& map)
    { 
        for(auto row {0uz}; row < getHeight(); ++row)
        {
            for(auto col {0uz}; col < getLength(); ++col)
            {
                levelMap[row][col] = Tile{ map[row][col], Position{row,col} };
            }
        }
    }
    std::size_t getLength() const { return LevelInfo::mapLength; }
    std::size_t getHeight() const { return LevelInfo::mapHeight; }
    Tile getTileAtPosition(std::size_t row, std::size_t col) const
    {
        return levelMap[row][col];
    }
    void draw()
    {
       for(auto row {0uz}; row < LevelInfo::mapHeight; ++row)
        {
            for(auto col {0uz}; col < LevelInfo::mapLength; ++col)
            {
                std::print("{}",getTileAtPosition(row,col).getSymbol()); 
            }
            std::println();
        } 
    }
};