#pragma once

#include "Position.h"
#include "LevelInfo.h"
#include <array>

struct Tile;

class Board
{
    public:
    using GameMap = std::array<std::array<Tile,LevelInfo::mapLength>,LevelInfo::mapHeight>;

    

};