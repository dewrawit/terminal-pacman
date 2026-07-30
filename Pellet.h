#pragma once

#include "AsciiData.h"

class Pellet
{
    public:
    enum class Type { normal, super };

    private:
    char m_symbol{AsciiData::NormalPelletSymbol};
    Type m_type{Type::normal};

    public:
    Pellet(char symbol, Type type)
        : m_symbol{ symbol }
        , m_type{ type }
    { }


};