
#include "GameState.h"

int main()
{
    Board board{LevelInfo::map};
    GameState gameState{board};

    gameState.getBoard().draw();
    return 0;
}