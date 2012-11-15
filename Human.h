#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "IO.h"

class Human : public Player {
private:
	//Human player needs access to the IO
	IO *io;
public:
	Human(int color, Board* board, IO *io);
	bool play();
	XY choosePiece();
	XY chooseTarget();
	XY chooseTarget(vector<XY>& positions);
	XY chooseKillPiece(vector<XY>& killPositions);
	XY chooseKillTarget(vector<XY>& targetPositions);
};


#endif