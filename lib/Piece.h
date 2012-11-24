#ifndef PIECE_H
#define PIECE_H

#include "Color.h"

/**
 * PieceType enum
 */
namespace PieceType {

    enum {
        MAN = 1,
        KING = 2
    };
}
/**
 * Piece class
 */
class Piece {
private:
    //Color (BLACK/WHITE)
    int color;
    //Type (MAN/KING)
    int type;
public:
    //No default constructor
    Piece() = delete;
    
    /**
     * Constructor
     * @param color The piece color
     * @param type The piece type
     */
    Piece(int color = Color::WHITE, int type = PieceType::MAN);

    int getColor() const {
        return color;
    }

    int getType() const {
        return type;
    }
    /**
     * Promote the piece from MAN to KING
     */
    void promote();
};
#endif