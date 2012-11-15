#include "Human.h"

Human::Human(int color, Board* board, IO* io) : Player(color, board) {
    this->io = io;
}

void Human::choosePiece() {
    selectedXY = io->getMovementPiece();
    piece = board->getPiece(selectedXY);
}

void Human::chooseTarget() {
    targetXY = io->getMovementTarget();
    targetPiece = board->getPiece(targetXY);
}

bool Human::play() {
    //Ask the user the piece he wants to select
    choosePiece();
    //Invalid piece
    if (piece == 0) {
        io->message("No piece.\n");
        return false;
    }
    if (piece->getColor() != color) {
        io->message("Invalid piece.\n");
        return false;
    }
    io->message("Valid piece.\n");
    chooseTarget();
    int max = board->getSize()-1;
    int x = targetXY.getX();
    int y = targetXY.getY();
    if (x > max || y > max || x < 0 || y < 0){
        io->message("Invalid target.\n");
        return false;
    }

    //The coordinate must not be the same
    if (!board->movePiece(selectedXY, targetXY)) {
        io->message("Invalid move.\n");
        return false;
    }
    io->message("Valid move.\n");
    return true;
}

XY Human::chooseKillPiece(vector<XY>& killPositions) {
    //Only one possibility...
    if (killPositions.size() == 1) {
        return killPositions[0];
    } else {
        io->message("Choose your piece: \n");
        return io->choosePosition(killPositions);
    }
}

XY Human::chooseKillTarget(vector<XY>& killTargets) {
    //Only one possibility...
    if (killTargets.size() == 1) {
        return killTargets[0];
    } else {
        io->message("Choose your target: \n");
        return io->choosePosition(killTargets);
    }
}