#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "XY.h"
#include "Types.h"

#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>
#include <map>

using namespace std;


//Constants
static const char BLANK_CHAR = ' ';
static const char WHITE_MAN_CHAR = 'A';
static const char WHITE_KING_CHAR = '@';
static const char BLACK_MAN_CHAR = '8';
static const char BLACK_KING_CHAR = '&';

static const uint MAX_BOARD_SIZE = 12;

/**
 * Board class
 * Responsible for performing and validating movements and kills
 * Keeps track of all pieces
 */
class Board {
private:
    //The size of the board (@see MAX_BOARD_SIZE constant)
    uint size;
    //Number of white pieces "alive"
    uint whiteCount;
    //Number of black pieces "alive"
    uint blackCount;
    //The piece matrix
    vector<vector<Piece*> > board;
public:
    /**
     * Constructor
     * @param size The size of the board (always square)
     */
    Board(uint size = 8);
    /**
     * Copy constructor
     * Necessary because shallow copy must not occur
     * @param copy
     */
    Board(const Board& copy);
    
    /**
     * Destructor
     */
    virtual ~Board();
    /**
     * Initializes the board placing the pieces
     * Only will be called when a new game is created
     */
    void init();
    /**
     * Load the given format
     * Here is an example of board
     * 
     *   0 0 0 0 0 0 0 0
     *   0 0 0 0 0 0 0 0
     *   0 A A 0 8 0 8 0
     *   0 0 0 @ 0 8 0 0
     *   0 0 0 0 8 0 8 0
     *   0 0 0 0 0 0 0 0
     *   0 0 0 0 0 0 0 0
     *   0 0 0 0 0 0 0 0
     * 
     * @param board
     */
    void load(const vector<string>& board);

    /**
     * Return the size of the board
     * @return 
     */
    uint getSize() const {
        return size;
    }

    /**
     * Return the number of white pieces "alive"
     * @return 
     */
    uint getWhiteCount() const {
        return whiteCount;
    }

    /**
     * Return the number of black pieces "alive"
     * @return 
     */
    uint getBlackCount() const {
        return blackCount;
    }
    /**
     * Return the piece at the given coordinate, if any
     * @param xy
     * @return 
     */
    Piece* getPiece(const XY& xy) const;
    //Verify if the given position has a piece
    /**
     * Return whether there is a piece at the given coordinate
     * @param xy
     * @return 
     */
    bool hasPiece(const XY& xy) const;
    //Set the given piece to the given position
    /**
     * Set the given piece to the given position
     * @param piece The piece to set
     * @param xy Where the piece will be set
     * @return true if the coordinate is valid, false otherwise
     */
    bool setPiece(Piece* piece, const XY& xy);
    /**
     * Remove the piece at the given coordinate
     * Frees memory associated with that piece
     * Decrements the appropriate counter (whiteCounter or blackCounter) 
     * @param xy The target piece
     * @return true if the coordinate was valid and the piece could be removed
     */
    bool removePiece(const XY& xy);
    /**
     * Try to perform a move or a kill
     * @param xy The coordinate of the piece selected to perform the move/kill
     * @param targetXY The target coordinate (if it's a kill, it should be the exact coordinate of the target piece)
     * @return true if the move/kill was successfull, false otherwise
     */
    bool movePiece(const XY& xy, const XY& targetXY);
    /**
     * Promote all the man that are on the first or last row according to the color
     * @return the number of pieces promoted
     */
    uint promote();
    /**
     * Verify if there are any mandatory adjacent kills for the given piece coordinates
     * @param xy The coordinates of the piece to be verified
     * @return A list of adjacent kill positions
     */
    vector<XY> verifyAdjacentKills(XY xy) const;
    /**
     * Verify if the xy is a valid piece and targetXY is a valid target and the kill can be performed
     * @param xy The piece position
     * @param targetXY The target piece position
     * @return Whether it's possible to kill or not
     */
    bool verifyKill(XY xy, XY targetXY) const;
    /**
     * Verify and return all possible kills for the given player color
     * @param playerColor
     * @param possibleKillsCount The number of possible kills
     * @return 
     */
    uint verifyPossibleKills(uint playerColor, map<XY, vector<XY> >& possibleKills, vector<XY>& piecesXY) const;
};

#endif