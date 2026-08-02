#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Pellet.h"
#include "LevelInfo.h"
#include <memory>
#include <vector>
#include <array>

class GameState
{
private:
    Board m_board{};
    Pacman m_pacman{};
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};
    std::vector<Pellet> m_pellets{};
    int m_lives { 3 };
    using AsciiMap = std::array<std::string_view,LevelInfo::mapHeight>;

public:

    //Game state must read board data to create entites at correct position
    GameState(const AsciiMap& board);

    const Board& getBoard() const;
    Board& getBoard();

    const Pacman& getPacman() const;
    Pacman& getPacman();

    const Ghost& ghostAt(const Position& pos) const;
    Ghost& ghostAt(const Position& pos);
    bool containsGhostAt(const Position& pos) const;

    const Pellet& pelletAt(const Position& pos) const;
    void removePelletAt(const Position& pos);
    bool containsPelletAt(const Position& pos) const;

    void makeAllGhostsScared();
    void updateGhostTimer();
    void updateTileData();
    void update();
    void renderBoard();
    char getGameObjectSymbolAt(const Position& pos);
    char getGameObjectSymbolAt(int row, int col);
    bool win();
    bool lose();
};