#pragma once

#include <iostream>

struct Position
{
    int row{};
    int col{};

    Position operator+(std::pair<int,int> direction) const
    {
        auto [movRow, movCol] { direction };
        return Position{row + movRow, col + movCol};
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
};