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

    template <std::size_t Height>
    Board(const std::array<std::string_view,Height>& map)
    { 
        for(auto row {0uz}; row < static_cast<std::size_t>(getHeight()); ++row)
        {
            for(auto col {0uz}; col < static_cast<std::size_t>(getLength()); ++col)
            {
                bool walkable{ map[row][col] == AsciiData::WallSymbol ? false : true };

                levelMap[row][col] = Tile{ walkable, 
                    Position{static_cast<int>(row),static_cast<int>(col)} 
                };
            }
        }
    }
    int getLength() const { return LevelInfo::mapLength; }
    int getHeight() const { return LevelInfo::mapHeight; }
    Tile& getTileAtPosition(const Position& pos)
    {
        return levelMap[static_cast<std::size_t>(pos.row)][static_cast<std::size_t>(pos.col)];
    }
    const Tile& getTileAtPosition(const Position& pos) const
    {
        return levelMap[static_cast<std::size_t>(pos.row)][static_cast<std::size_t>(pos.col)];
    }
    Tile& getTileAtPosition(int row, int col)
    {
        return levelMap[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];
    }
    const Tile& getTileAtPosition(int row, int col) const
    {
        return levelMap[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];
    }

    // A Tile shouldn't store entity symbol its pain in the ass when moving things
    // Whoever thought about this should get a brain check (me)
    // void draw()
    // {
    //    for(int row {0}; row < LevelInfo::mapHeight; ++row)
    //     {
    //         for(int col {0}; col < LevelInfo::mapLength; ++col)
    //         {
    //             std::print("{}",getTileAtPosition(row,col).getSymbol()); 
    //         }
    //         std::println();
    //     } 
    // }

};