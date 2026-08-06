#pragma once

#include <iostream>
#include <utility>

struct Position
{
    int row{};
    int col{};

    Position operator+(std::pair<int, int> direction) const;
    Position operator+(const Position& pos) const;
    Position operator-(const Position& pos) const;

    friend std::ostream& operator<<(std::ostream& out, const Position& pos);

    bool operator==(const Position& pos) const;

    bool inBounds() const;
    bool outOfBounds() const;

    double distance(const Position& pos) const;

    static Position getRandomPosition(); 
};