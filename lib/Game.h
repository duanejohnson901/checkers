#ifndef GAME_H
#define GAME_H

//#define CONSOLE

#include "Board.h"
#include "Drawer.h"
#include "ConsoleDrawer.h"
#include "IO.h"
#include "ConsoleIO.h"
#include "Player.h"
#include "AI.h"
#include "Human.h"
#include "Types.h"

#include <memory>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <stdexcept>

#include <windows.h>

using namespace std;

/**
 * Game class
 * Constrols the game loop
 */
class Game {
private:
    //The color of the current player
    uint currentPlayerColor;
    //The game mode @see GameMode enum below
    uint mode;
    //The current turn number (first is 0)
    uint turn;
    //The level of the AI from 1 to 9 (if any) @see AILevel enums
    uint aiLevel;
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
     * Load the game from a given file
     * @param filename
     */
    Game(const string& loadFileName);
    /**
     * Create a new game
     * @param mode The game mode (@see GameMode enum)
     * @param boardSize The size of the board
     * @param startingPlayerColor The starting player color
     */
    Game(uint mode, uint boardSize = 8, uint startingPlayerColor = Color::WHITE, uint aiLevel = AILevel::MEDIUM);
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
     * Create a new game
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
     * Show the game menu (only for human players) and waits for input
     * @return Whether the game should continue or not
     */
    bool menu();
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