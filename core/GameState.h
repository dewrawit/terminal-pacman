#pragma once

#include "Pacman.h"
#include "../ghosts/AllGhosts.h"
#include "Board.h"
#include "Pellet.h"
#include "LevelInfo.h"
#include "Timer.h"
#include "Position.h"
#include <memory>
#include <vector>
#include <array>

class GameState
{
public:
    using TimerArray = std::array<Timer,Timer::TimerTypes::maxTimerTypes>;
    enum Character { pacman, blinky, pinky, inky, clyde, maxCharacter };

private:
    Board m_board{};
    Pacman m_pacman{};
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};
    std::vector<Pellet> m_pellets{};
    TimerArray m_globalTimers{};
    int m_lives { 3 };
    using AsciiMap = std::array<std::string_view,LevelInfo::mapHeight>;
    int m_score { 0 };
    int m_modeRepeat { 1 };
    int m_ghostConsumedPerPower { 0 };
    const int m_modeRepeatPermanentChase { 4 };

    std::array<Position, Character::maxCharacter> m_spawnPoints{};
    

public:

    //Game state must read board data to create entites at correct position
    GameState(const AsciiMap& board);

    const Board& getBoard() const;
    Board& getBoard();

    const Pacman& getPacman() const;
    Pacman& getPacman();

    std::vector<std::unique_ptr<Ghost>>& getGhosts();
    const std::vector<std::unique_ptr<Ghost>>& getGhosts() const;

    const Ghost& ghostAt(const Position& pos) const;
    Ghost& ghostAt(const Position& pos);
    bool containsGhostAt(const Position& pos) const;

    const Pellet& pelletAt(const Position& pos) const;
    void removePelletAt(const Position& pos);
    bool containsPelletAt(const Position& pos) const;

    void makeAllGhosts(Ghost::GhostState state);
    void updateTimer();
    void update();
    void renderBoard();
    char getGameObjectSymbolAt(const Position& pos);
    char getGameObjectSymbolAt(int row, int col);
    bool win() const;
    bool lose() const;
    bool oneTimerActive(); //for assert check, only 1 global timer must run at a time
    void applyGhostCurrentTimerEffect();

    Timer& getTimer(Timer::TimerTypes type); 
    Timer& getActiveTimer();
    void activateTimerState(Timer::TimerTypes type);
    void startGhostsWaitTimer();
    int getLives() const;
    void loseALife();
    void respawn();
    void retargetGhosts();
    void moveGhosts();

    const Blinky& getBlinky() const; //for inky's AI
    void flipGhostsDirection();

    int getScore() const;
    void increaseScore(int amount);

    void resetModeRepeat();
    void resetGhostConsumedStacks();
    int getGhostConsumedStacks() const;
    void incrementGhostConsumedStacks();

    bool inPermaChase() const;
    void setPausedTimer(const Timer& timer);
};