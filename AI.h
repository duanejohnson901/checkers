#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Board.h"

class AI : public Player {
public:
    AI(int color, Board* board);
    bool play();
    void choosePiece();
    void chooseTarget();
    XY chooseKillPiece(vector<XY>& killPositions);
    XY chooseKillTarget(vector<XY>& targetPositions);
};

#endif