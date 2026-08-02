#pragma once

#include <string>

namespace Color
{
    constexpr std::string WALLBLUE = "\033[34m"; //BLACK TEXT BLUE BG
    constexpr std::string RESET   = "\033[0m";
    constexpr std::string RED     = "\033[37;41m";
    constexpr std::string YELLOW  = "\033[37;43m";

    constexpr std::string CYAN    = "\033[37;44m";
    //Actually blue but same reason as why i use magenta for pink
    
    constexpr std::string PINK    = "\033[37;45m"; 
    //Actually magenta but i have to use it 
    //because terminal can't make pink background have white text

    constexpr std::string ORANGE  = "\033[37;48;5;130m"; 
}
