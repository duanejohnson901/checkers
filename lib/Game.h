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
#include <fstream>
#include <ctime>

#include <windows.h>

using namespace std;

class Game {
private:
    //The color of the current player
    int currentPlayerColor;
    int mode;
    //The current turn number (first is 0)
    int turn;
    //Flag to control the game loop
    bool ended;
    //Pointer to the game board
    Board* board;
    //Pointer to the game drawer
    Drawer* drawer;
    //Pointer to the IO
    IO* io;
    //Pointer to the white player
    Player* whitePlayer;
    //Pointer to the black player
    Player* blackPlayer;
public:
    //No default constructor
    Game() = delete;
    /**
     * Loads the game from a given file
     * @param filename
     */
    Game(const string& loadFileName);
    /**
     * Creates a new game
     * @param mode The game mode (@see GameMode enum)
     * @param boardSize The size of the board
     * @param startingPlayerColor The starting player color
     */
    Game(int mode, int boardSize = 8, int startingPlayerColor = Color::WHITE);
    virtual ~Game();
    /**
     * Must be called to start the game
     */
    void start();
private:
    /**
     * Saves the game to a given file
     * Create it if it does not exists
     * @param filename
     */
    void save(const string& filename);
    /**
     * Creates a new game
     */
    void newGame();
    /**
     * Initialize the players according to the game mode
     */
    void initMode();
    /**
     * Initialize the board
     */
    void initializeBoard();
    /**
     * Verify if there are any mandatory adjacent kills for the given piece coordinates
     * @param xy The coordinates of the piece to be verified
     * @return A list of adjacent kill positions
     */
    vector<XY> verifyAdjacentKills(XY xy);
    /**
     * Verify if the xy is a valid piece and targetXY is a valid target and the kill can be performed
     * @param xy The piece position
     * @param targetXY The target piece position
     * @return Whether it's possible to kill or not
     */
    bool verifyKill(XY xy, XY targetXY);
};

/**
 * GameMode num
 */
namespace GameMode {

    enum {
        PLAYER_VS_PLAYER = 1,
        PLAYER_VS_AI = 2,
        AI_VS_AI = 3
    };
};
#endif