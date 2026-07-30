#pragma once

#include "Position.h"
#include "LevelInfo.h"
#include "Tile.h"
#include <array>

class Board
{
    public:
    using GameMap = std::array<std::array<Tile,LevelInfo::mapLength>,LevelInfo::mapHeight>;

    private:
    GameMap levelMap {};

    public:
    Board() = default;
    template <std::size_t Length, std::size_t Height>
    Board(const std::array<std::array<std::string_view,Length>,Height>& map)
    { 
        for(auto row {0uz}; row < Height; ++row)
        {
            for(auto col {0uz}; col < Length; ++col)
            {
                levelMap[row][col] = Tile{ map[row][col], Position{row,col} };
            }
        }
    }
    int getLength() const { return LevelInfo::mapLength; }
    int getHeight() const { return LevelInfo::mapHeight; }
    Tile getTileAtPosition(std::size_t row, std::size_t col) const
    {
        return levelMap[row][col];
    }
};