#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "XY.h"

#include <vector>

using namespace std;


class Player
{
protected:
	//Player color
	int color;
	Board* board;
	//The selected piece
	Piece* piece;
	//The target piece
	Piece* targetPiece;
	//The coordinates of the selected piece
	XY selectedXY;
public:
	Player(int color, Board *board);
	virtual bool play() = 0;
	virtual XY choosePiece() = 0;
	virtual XY chooseTarget() = 0;
	virtual XY chooseTarget(vector<XY>& pieces) = 0;
	virtual XY chooseKillPiece(vector<XY>& killPositions) = 0;
	virtual XY chooseKillTarget(vector<XY>& targetPositions) = 0;
};
#endif