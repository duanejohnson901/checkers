#ifndef PIECE_H
#define PIECE_H

#include "Types.h"
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
    uint color;
    //Type (MAN/KING)
    uint type;
public:
    //No default constructor
    Piece() = delete;
    
    /**
     * Constructor
     * @param color The piece color
     * @param type The piece type
     */
    Piece(uint color = Color::WHITE, uint type = PieceType::MAN);

    uint getColor() const {
        return color;
    }

    uint getType() const {
        return type;
    }
    /**
     * Promote the piece from MAN to KING
     */
    void promote();
};
#endif