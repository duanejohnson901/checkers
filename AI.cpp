#include "AI.h"

AI::AI(int color, Board* board) : Player(color, board) {
}

bool AI::play() {
    return true;
}

void AI::choosePiece() {
}

void AI::chooseTarget() {
}

XY AI::chooseKillPiece(vector<XY>& killPositions) {
    return XY(0, 0);
}

XY AI::chooseKillTarget(vector<XY>& targetPositions) {
    return XY(0, 0);
}
