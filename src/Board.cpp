#include <vector>
#include <string>

#include "../lib/Board.h"

Board::Board(int size) {
    this->size = size;
    this->whiteCount = 0;
    this->blackCount = 0;
    for (int i = 0; i < size; i++) {
        board.push_back(vector<Piece*>());
        for (int j = 0; j < size; j++) {
            board[i].push_back(0);
        }
    }
}

Board::~Board() {
}

bool Board::hasPiece(const XY& xy) const {
    int max = size - 1;
    int x = xy.getX();
    int y = xy.getY();
    //Out of the array bounds
    if (x > max || y > max || x < 0 || y < 0) return false;
    return this->board[x][y] != 0;
}

Piece* Board::getPiece(const XY& xy) const {
    int x = xy.getX();
    int y = xy.getY();
    int max = size - 1;
    //Out of the array bounds
    if (x > max || y > max || x < 0 || y < 0) return 0;
    return this->board[x][y];
}

bool Board::setPiece(Piece *piece, const XY& xy) {
    int x = xy.getX();
    int y = xy.getY();
    int max = size - 1;
    //Out of the array bounds
    if (x > max || y > max || x < 0 || y < 0) return false;
    this->board[x][y] = piece;
    return true;
}

void Board::init() {
    //Place the pieces
    //White Pieces
    for (int x = 0; x < size; x += 2) {
        for (int y = 0; y < (size * 3) / 8; y++) {
            this->setPiece(new Piece(Color::WHITE), XY(x + (y % 2 == 0 ? 0 : 1), y));
            this->whiteCount++;
        }
    }
    //Black Pieces
    for (int x = 0; x < size; x += 2) {
        for (int y = (size * 5) / 8; y < size; y++) {
            this->setPiece(new Piece(Color::BLACK), XY(x + (y % 2 == 0 ? 0 : 1), y));
            this->blackCount++;
        }
    }
}

void Board::load(const vector<string>& board) {
    whiteCount = blackCount = 0;
    for (int y = 0; y < board.size(); y++) {
        string line = board[y];
        for (int x = 0; x < size; x++) {
            char c = line.at(x * 2);
            if (c != '0') {
                int color = 0;
                int type = 0;
                switch (c) {
                    case '@':
                        color = Color::WHITE;
                        type = PieceType::KING;
                        whiteCount++;
                        break;
                    case '&':
                        color = Color::BLACK;
                        type = PieceType::KING;
                        blackCount++;
                        break;
                    case 'A':
                        color = Color::WHITE;
                        type = PieceType::MAN;
                        whiteCount++;
                        break;
                    case '8':
                        color = Color::BLACK;
                        type = PieceType::MAN;
                        blackCount++;
                        break;
                }
                Piece *piece = new Piece(color, type);
                setPiece(piece, XY(x, y));
            }
        }
    }
}

bool Board::removePiece(const XY& xy) {
    int x = xy.getX();
    int y = xy.getY();
    int max = size - 1;
    //Out of the array bounds
    if (x > max || y > max || x < 0 || y < 0) return false;

    Piece* piece = this->board[x][y];
    this->board[x][y] = 0;

    if (piece == 0) {
        return false;
    } else {
        if (piece->getColor() == Color::WHITE) {
            this->whiteCount--;
        } else {
            this->blackCount--;
        }
        delete piece;
        return true;
    }
}

int Board::promote() {
    int promoted = 0;
    for (int x = 0; x < size; x++) {
        //First row
        Piece* piece = this->board[x][0];
        if (piece != 0 && piece->getColor() == Color::BLACK && piece->getType() == PieceType::MAN) {
            piece->promote();
            promoted++;
        }
        //Last row
        piece = this->board[x][size - 1];
        if (piece != 0 && piece->getColor() == Color::WHITE && piece->getType() == PieceType::MAN) {
            piece->promote();
            promoted++;
        }
    }
    return promoted;
}

bool Board::movePiece(const XY& xy, const XY& targetXY) {
    int x = xy.getX();
    int y = xy.getY();
    int targetX = targetXY.getX();
    int targetY = targetXY.getY();
    //The coordinate must not be the same
    if (x == targetX && y == targetY) {
        return false;
    }
    //Only diagonal movements are allowed
    //The sum of the absolute differences of the X and Y coordinates must be 2
    int xMovement = targetX - x;
    int yMovement = targetY - y;
    int xMovementModulus = abs(xMovement);
    int yMovementModulus = abs(yMovement);
    int val = abs(xMovement) + abs(yMovement);
    Piece* targetPiece = this->board[targetX][targetY];
    Piece* piece = this->board[x][y];
    //Man pieces can only advance one diagonal
    if (piece->getType() == PieceType::MAN && val != 2) {
        return false;
    } else if (piece->getType() == PieceType::KING && xMovementModulus != yMovementModulus) {
        return false;
    }
    int color = piece->getColor();
    if (targetPiece == 0) {
        //It's a move because there is no piece on the target coordinate
        //Move the piece
        if (piece->getType() == PieceType::MAN) {
            switch (color) {
                case Color::WHITE:
                    //Can only move down (y can increment)
                    if (yMovement < 0) {
                        return false;
                    }
                    break;
                case Color::BLACK:
                    //Can only move up (x can increment)
                    if (yMovement > 0) {
                        return false;
                    }
                    break;
            }
        }

        this->board[x][y] = 0;
        this->board[targetX][targetY] = piece;
        return true;
    } else if (targetPiece->getColor() == piece->getColor()) {
        return false;
    } else {
        //The "next" position should be blank in order to perform a kill
        int blankX = x + xMovement + (xMovement>0?1:-1);
        int blankY = y + yMovement + (yMovement>0?1:-1);
        XY blankXY(blankX, blankY);

        if (piece->getType() == PieceType::MAN) {
            switch (color) {
                case Color::WHITE:
                    //Can only move down (y can increment)
                    if (yMovement < 0) {
                        return false;
                    }
                    break;
                case Color::BLACK:
                    //Can only move up (x can increment)
                    if (yMovement > 0) {
                        return false;
                    }
                    break;
            }
        }
        if (!this->hasPiece(blankXY)) {
            //Kills the piece
            this->removePiece(targetXY);
            this->board[blankX][blankY] = piece;
            this->board[x][y] = 0;
            return true;
        } else {
            return false;
        }
    }
}