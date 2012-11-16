#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "XY.h"
#include "IO.h"

#include <vector>
#include <algorithm>

using namespace std;

class Player {
protected:
    IO *io;
    //Player color
    int color;
    Board* board;
public:
    Player(int color, Board* board, IO *io);
    virtual bool play() = 0;
    virtual XY chooseKillPiece(vector<XY>& killPositions) = 0;
    virtual XY chooseKillTarget(vector<XY>& targetPositions) = 0;
    virtual int getType() const = 0;
};
namespace PlayerType {
    enum { AI = 1, HUMAN = 2 };
};
#endif