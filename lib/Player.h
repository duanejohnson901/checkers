#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "XY.h"
#include "IO.h"

#include <vector>
#include <algorithm>

using namespace std;

/**
 * Player class
 * Abstract base class for AI and Human
 */
class Player {
protected:
    //Player color
    uint color;
    //IO for intereaction (displaying messages, gathering user input, etc)
    IO& io;
    //Reference to the board
    Board& board;
public:
    /**
     * No default constructor
     */
    Player() = delete;
    /**
     * Constructor
     * @param color The player color (BLACK/WHITE)
     * @param board A reference to the board
     * @param io A reference to the IO system for interactions
     */
    Player(uint color, Board& board, IO& io);
    /**
     * 
     * @return 
     */
    virtual bool play() = 0;
    /**
     * Chooses a piece (from the player) which will be used to perform a kill (mandatory kill)
     * @param killPositions
     * @param possibleKills A map containing all possible killer pieces and their targets
     * @return 
     */
    virtual XY chooseKillPiece(const vector<XY>& killPositions, const map<XY, vector<XY> >& possibleKills) const = 0;
    /**
     * Chooses a target piece which will be killed based on a list of targets using a previously selected piece from chooseKillPiece()
     * @param targetPositions The list of the kill possibilities (positions)
     * @return The position of the piece selected to kill
     */
    virtual XY chooseKillTarget(const vector<XY>& targetPositions) const = 0;
    /**
     * Returns the player type
     * Must be implemented and return AI or HUMAN
     * @return 
     */
    virtual uint getType() const = 0;
};

/**
 * PlayerType enum
 */
namespace PlayerType {
    enum { AI = 1, HUMAN = 2 };
};
#endif