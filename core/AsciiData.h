#pragma once

namespace AsciiData
{
    constexpr char PacmanSymbol {'P'};
    constexpr char BlinkySymbol {'B'};

    //'P' collides with pacman, cause problem when reading board from levelInfo
    constexpr char PinkySymbol {'N'}; 
    
    constexpr char InkySymbol {'I'};
    constexpr char ClydeSymbol {'C'};
    constexpr char NormalPelletSymbol {'.'};
    constexpr char SuperPelletSymbol {'o'};
    constexpr char WallSymbol {'#'};
    constexpr char GhostDoorSymbol {'='};
    constexpr char EmptySymbol {' '};
}