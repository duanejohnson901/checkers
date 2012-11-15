#include "AI.h"

AI::AI(int color, Board* board) : Player(color, board) {
}

bool AI::play() {
	return true;
}

XY AI::choosePiece() {
	XY xy(0, 0);
	return xy;
}

XY AI::chooseTarget() {
	XY xy(0, 0);
	return xy;
}
XY AI::chooseTarget(vector<XY>& positions) {
	XY xy(0, 0);
	return xy;
}

XY AI::chooseKillPiece(vector<XY>& killPositions) {
	return XY(0, 0);
}
XY AI::chooseKillTarget(vector<XY>& targetPositions) {
	return XY(0, 0);
}
