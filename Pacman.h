#pragma once

#include <string>
#include <string_view>

class Pacman
{
    private:
    std::string m_name { "Pac-man" };
    char m_symbol { 'P' };
    bool m_alive { true };

    public:
    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    bool isAlive() const { return m_alive; }
    bool isDead() const { return !m_alive; }
};