#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
#include "Types.h"

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
    Human() = delete;
    Human(uint color, Board& board, IO& io);
    //Inherited
    bool play();
    void choosePiece();
    void chooseTarget();
    XY chooseKillPiece(const vector<XY>& killPositions) const;
    XY chooseKillTarget(const vector<XY>& targetPositions) const;

    uint getType() const {
        return PlayerType::HUMAN;
    }
};


#endif