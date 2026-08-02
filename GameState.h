#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Pellet.h"
#include "Position.h"
#include "AsciiData.h"
#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>
#include <ranges>

class GameState
{
private:
    Board m_board{};
    Pacman m_pacman{};
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};
    std::vector<Pellet> m_pellets{};

public:

    //Game state must read board data to create entites at correct position
    GameState(const Board& board);

    const Board& getBoard() const;
    Board& getBoard();

    const Pacman& getPacman() const;
    Pacman& getPacman();

    const Ghost& ghostAt(const Position& pos) const;
    Ghost& ghostAt(const Position& pos);

    void removePelletAt(const Position& pos);
    void makeAllGhostsScared();
    void updateGhostTimer();
    void updateTileData();
    void update();
};