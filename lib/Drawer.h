#ifndef DRAWER_H
#define DRAWER_H

#include "Board.h"
#include "Piece.h"

class Drawer
{
public:
	virtual void clear() = 0;
	virtual void drawInfo(int turn, int currentPlayerColor, int whitePieces, int blackPieces) = 0;
	virtual void drawBoard(Board *board) = 0;
};

#endif