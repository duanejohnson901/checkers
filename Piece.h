#ifndef PIECE_H
#define PIECE_H

namespace PieceColor {

    enum {
        WHITE = 1,
        BLACK = 2
    };
};
namespace PieceType {

    enum {
        MAN = 1,
        KING = 2
    };
};

class Piece {
private:
    int color;
    int type;
public:
    Piece(int color = PieceColor::WHITE, int type = PieceType::MAN);

    int getColor() const {
        return color;
    }

    int getType() const {
        return type;
    }
    void promote();
};

#endif