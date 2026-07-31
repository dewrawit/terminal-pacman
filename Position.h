#pragma once

struct Position
{
    int row{};
    int col{};

    Position operator+(std::pair<int,int> direction) const
    {
        auto [movRow, movCol] { direction };
        return Position{row + movRow, col + movCol};
    }
};