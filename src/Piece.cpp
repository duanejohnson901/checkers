#include "../lib/Piece.h"

Piece::Piece(uint color, uint type) {
    this->color = color;
    this->type = type;
}

void Piece::promote() {
    this->type = PieceType::KING;
}