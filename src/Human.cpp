#include "../lib/Human.h"

Human::Human(uint color, Board& board, IO& io) : Player(color, board, io) {
    this->piece = 0;
    this->targetPiece = 0;
}

void Human::choosePiece() {
    selectedXY = io.getMovementPiece();
    piece = board.getPiece(selectedXY);
}

void Human::chooseTarget() {
    targetXY = io.getMovementTarget();
    targetPiece = board.getPiece(targetXY);
}

bool Human::play() {
    //Ask the user the piece he wants to select
    choosePiece();
    //Invalid piece
    if (piece == 0) {
        io.message("No piece.\n");
        return false;
    }
    if (piece->getColor() != color) {
        io.message("Invalid piece.\n");
        return false;
    }
    io.message("Valid piece.\n");
    chooseTarget();
    uint max = board.getSize()-1;
    uint x = targetXY.getX();
    uint y = targetXY.getY();
    if (x > max || y > max){
        io.message("Invalid target.\n");
        return false;
    }

    //The coordinate must not be the same
    if (!board.movePiece(selectedXY, targetXY)) {
        io.message("Invalid move.\n");
        return false;
    }
    io.message("Valid move.\n");
    return true;
}

XY Human::chooseKillPiece(const vector<XY>& killPositions) const {
    //Only one possibility...
    if (killPositions.size() == 1) {
        return killPositions[0];
    } else {
        io.message("Choose your piece: \n");
        return io.choosePosition(killPositions);
    }
}

XY Human::chooseKillTarget(const vector<XY>& killTargets) const {
    //Only one possibility...
    if (killTargets.size() == 1) {
        return killTargets[0];
    } else {
        io.message("Choose your target: \n");
        return io.choosePosition(killTargets);
    }
}