#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Random.h"
#include <algorithm>

using namespace std;

class AI : public Player {
public:
    AI(int color, Board* board, IO* io);
    bool play();
    XY chooseKillPiece(vector<XY>& killPositions);
    XY chooseKillTarget(vector<XY>& targetPositions);
    int getType() const { return PlayerType::AI; }
};

#endif