#include "../lib/Piece.h"

Piece::Piece(int color, int type) {
    this->color = color;
    this->type = type;
}

void Piece::promote() {
    this->type = PieceType::KING;
}