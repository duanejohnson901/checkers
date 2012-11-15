#include "Human.h"

Human::Human(int color, Board* board, IO* io) : Player(color, board) {
    this->io = io;
}

XY Human::choosePiece() {
    XY xy = io->getMovementPiece();
    piece = board->getPiece(xy);
    return xy;
}

XY Human::chooseTarget() {
    XY xy = io->getMovementTarget();
    targetPiece = board->getPiece(xy);
    return xy;
}

XY Human::chooseTarget(vector<XY>& positions) {
    return XY(0, 0);
}

bool Human::play() {
    //Ask the user the piece he wants to select
    selectedXY = choosePiece();
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
    XY targetXY = chooseTarget();

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