#ifndef DRAWER_H
#define DRAWER_H

#include "Board.h"
#include "Piece.h"

/**
 * Drawer class
 * Responsible for drawing the game onto a screen
 * Abstract base class
 */
class Drawer {
public:
    /**
     * Clears the screen
     */
    virtual void clear() const = 0;
    /**
     * Draw basic information
     * @param turn The number of the turn
     * @param currentPlayerColor The color of the current player
     * @param whitePieces The number of remaining white pieces
     * @param blackPieces The number of remaining black pieces
     */
    virtual void drawInfo(int turn, int currentPlayerColor, int whitePieces, int blackPieces) const = 0;
    /**
     * Draw the board
     * @param board
     */
    virtual void drawBoard(const Board &board) const = 0;
};

#endif