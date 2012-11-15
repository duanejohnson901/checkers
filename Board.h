#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "XY.h"

#include <cmath>
#include <vector>
#include <string>

using namespace std;

class Board {
private:
    //The size of the board
    int size;
    //White and black pieces counter
    int whiteCount;
    int blackCount;
    //The piece matrix
    Piece*** board;

public:
    Board(int size = 8);
    virtual ~Board();

    //Initializes the board placing the pieces
    void init();
    void load(vector<string> board);
    //Returns the size of the board

    int getSize() const {
        return size;
    }

    int getWhiteCount() const {
        return whiteCount;
    }

    int getBlackCount() const {
        return blackCount;
    }
    //Returns the piece of the given position
    Piece* getPiece(XY xy) const;
    //Verify if the given position has a piece
    bool hasPiece(XY xy) const;
    //Set the given piece to the given position
    bool setPiece(Piece* piece, XY xy);
    //Remove the piece at the (x, y) coordinate
    bool removePiece(XY xy);
    //Perform a move or a kill
    bool movePiece(XY xy, XY targetXY);
    //Promote all the man that are on the first or last row according to the color
    int promote();
};

#endif