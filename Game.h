#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Drawer.h"
#include "ConsoleDrawer.h"
#include "IO.h"
#include "ConsoleIO.h"
#include "Player.h"
#include "AI.h"
#include "Human.h"

#include <memory>
#include <map>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Game {
private:
    int currentPlayerColor;
    int mode;
    int turn;
    bool ended;
    Board* board;
    Drawer* drawer;
    IO* io;
    Player* whitePlayer;
    Player* blackPlayer;
public:
    Game(int mode, int boardSize = 8, int startingPlayerColor = PieceColor::WHITE);
    virtual ~Game();

    void newGame();
    void load(const char* filename);
    void save(const char* filename);
    void initializeBoard();
private:
    void start();
    vector<XY> verifyAdjacentKills(XY xy);
    bool verifyKill(XY xy, XY targetXY);
};

namespace GameMode {

    enum {
        PLAYER_VS_PLAYER,
        PLAYER_VS_AI,
        AI_VS_AI
    };
};

#endif