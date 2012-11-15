#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
private:
    //The selected piece
    Piece* piece;
    //The target piece
    Piece* targetPiece;
    //The coordinates of the selected piece
    XY selectedXY;
    //The coordinates of the target piece
    XY targetXY;
public:
    Human(int color, Board* board, IO *io);
    bool play();
    void choosePiece();
    void chooseTarget();
    XY chooseKillPiece(vector<XY>& killPositions);
    XY chooseKillTarget(vector<XY>& targetPositions);

    int getType() const {
        return PlayerType::AI;
    }
};


#endif