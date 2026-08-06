#include "Position.h"
#include "LevelInfo.h"
#include <cmath>
#include <utility>
#include <iostream>

Position Position::operator+(std::pair<int, int> direction) const
{
    auto [movRow, movCol] = direction;
    return Position{row + movRow, col + movCol};
}

Position Position::operator+(const Position& pos) const
{
    return Position{row + pos.row, col + pos.col};
}

Position Position::operator-(const Position& pos) const
{
    return Position{row - pos.row, col - pos.col};
}

std::ostream& operator<<(std::ostream& out, const Position& pos)
{
    out << "(" << pos.row << "," << pos.col << ")";
    return out;
}

bool Position::operator==(const Position& pos) const
{
    return (row == pos.row) && (col == pos.col);
}

bool Position::inBounds() const
{
    return row >= 0 && row < LevelInfo::mapHeight
        && col >= 0 && col < LevelInfo::mapLength;
}

bool Position::outOfBounds() const
{
    return !inBounds();
}

double Position::distance(const Position& pos) const
{
    int dx = row - pos.row;
    int dy = col - pos.col;

    return std::sqrt((dx * dx) + (dy * dy));
}