#include "Player.h"

Player::Player(int color, Board* board, IO* io) {
    this->color = color;
    this->board = board;
    this->io = io;
}