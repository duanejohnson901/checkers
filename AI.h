#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Board.h"

class AI : public Player
{
public:
	AI(int color, Board* board);
	bool play();
	XY choosePiece();
	XY chooseTarget();
	XY chooseTarget(vector<XY>& pieces);
	XY chooseKillPiece(vector<XY>& killPositions);
	XY chooseKillTarget(vector<XY>& targetPositions);
};

#endif