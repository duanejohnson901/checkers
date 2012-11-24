#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Random.h"
#include <algorithm>

using namespace std;

class AI : public Player {
public:
    AI() = delete;
    AI(int color, Board& board, IO& io);
    bool play();
    XY chooseKillPiece(const vector<XY>& killPositions) const;
    XY chooseKillTarget(const vector<XY>& targetPositions) const;
    int getType() const { return PlayerType::AI; }
};

#endif