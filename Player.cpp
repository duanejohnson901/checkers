#include "Player.h"

Player::Player(int color, Board* board) {
	this->color = color;
	this->board = board;
	this->piece = 0;
	this->targetPiece = 0;
}