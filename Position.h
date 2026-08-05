#pragma once

#include <iostream>
#include "LevelInfo.h"
#include <cmath>

struct Position
{
    int row{};
    int col{};

    Position operator+(std::pair<int,int> direction) const
    {
        auto [movRow, movCol] { direction };
        return Position{row + movRow, col + movCol};
    }
    Position operator+(const Position& pos) const
    {
        return Position{row + pos.row, col + pos.col};
    }
    Position operator-(const Position& pos) const
    {
        return Position{row - pos.row, col - pos.col};
    }
    friend std::ostream& operator<<(std::ostream& out, const Position& pos)
    {
        out << "(" << pos.row << "," << pos.col << ")";
        return out;
    }
    bool operator==(const Position& pos) const
    {
        return (row == pos.row) && (col == pos.col);
    }
    bool inBounds() const
    {
        return row >= 0 && row < LevelInfo::mapHeight
        && col >= 0 && col < LevelInfo::mapLength;
    }
    bool outOfBounds() const
    {
        return !inBounds();
    }
    double distance(const Position& pos)
    {
        int dx { row - pos.row };
        int dy { col - pos.col };

        return std::sqrt ((dx * dx) + (dy * dy));
    }
};