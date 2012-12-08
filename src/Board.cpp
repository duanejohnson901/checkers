#include "../lib/Board.h"

Board::Board(uint size) {
    if (size > MAX_BOARD_SIZE) {
        throw new invalid_argument("Invalid board size");
    }
    this->size = size;
    this->whiteCount = 0;
    this->blackCount = 0;
    //Initialize the vectors with null
    for (uint i = 0; i < size; i++) {
        board.push_back(vector<Piece*>());
        for (uint j = 0; j < size; j++) {
            board[i].push_back(NULL);
        }
    }
}

Board::Board(const Board& copy) {
    this->size = copy.size;
    this->whiteCount = copy.whiteCount;
    this->blackCount = copy.blackCount;
    //Initialize the vectors with NULL
    for (uint i = 0; i < size; i++) {
        board.push_back(vector<Piece*>());
        for (uint j = 0; j < size; j++) {
            board[i].push_back(NULL);
        }
    }

    for (int x = 0; x < size; x++){ 
        for (int y = 0; y < size; y++) {
            if (copy.board[x][y] != NULL) {
                Piece* pieceCopy = new Piece(*copy.board[x][y]);
                this->board[x][y] = pieceCopy;
            }
        }
    }
}

Board::~Board() {
    //Delete any remaining pieces - this will occur for board copies
    for (int x = 0; x < size; x++){ 
        for (int y = 0; y < size; y++) {
            Piece* piece = board[x][y];
            if (piece != NULL) {
                delete piece;
            }
        }
    }
}

bool Board::hasPiece(const XY& xy) const {
    uint max = size - 1;
    uint x = xy.getX();
    uint y = xy.getY();
    //Out of the array bounds
    if (x > max || y > max) return false;
    return this->board[x][y] != NULL;
}

Piece* Board::getPiece(const XY& xy) const {
    uint x = xy.getX();
    uint y = xy.getY();
    uint max = size - 1;
    //Out of the array bounds
    if (x > max || y > max) return 0;
    return this->board[x][y];
}

bool Board::setPiece(Piece *piece, const XY& xy) {
    uint x = xy.getX();
    uint y = xy.getY();
    uint max = size - 1;
    //Out of the array bounds
    if (x > max || y > max) return false;
    this->board[x][y] = piece;
    return true;
}

void Board::init() {
    //Place the pieces
    //White Pieces
    for (uint x = 0; x < size; x += 2) {
        for (uint y = 0; y < (size * 3) / 8; y++) {
            this->setPiece(new Piece(Color::WHITE), XY(x + (y % 2 == 0 ? 0 : 1), y));
            this->whiteCount++;
        }
    }
    //Black Pieces
    for (uint x = 0; x < size; x += 2) {
        for (uint y = (size * 5) / 8; y < size; y++) {
            this->setPiece(new Piece(Color::BLACK), XY(x + (y % 2 == 0 ? 0 : 1), y));
            this->blackCount++;
        }
    }
}

void Board::load(const vector<string>& board) {
    whiteCount = blackCount = 0;
    for (uint y = 0; y < board.size(); y++) {
        string line = board[y];
        for (uint x = 0; x < size; x++) {
            char c = line.at(x * 2);
            if (c != BLANK_CHAR) {
                uint color = 0;
                uint type = 0;
                switch (c) {
                    case WHITE_KING_CHAR:
                        color = Color::WHITE;
                        type = PieceType::KING;
                        whiteCount++;
                        break;
                    case BLACK_KING_CHAR:
                        color = Color::BLACK;
                        type = PieceType::KING;
                        blackCount++;
                        break;
                    case WHITE_MAN_CHAR:
                        color = Color::WHITE;
                        type = PieceType::MAN;
                        whiteCount++;
                        break;
                    case BLACK_MAN_CHAR:
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
    uint x = xy.getX();
    uint y = xy.getY();
    uint max = size - 1;
    //Out of the array bounds
    if (x > max || y > max) return false;

    Piece* piece = this->board[x][y];
    this->board[x][y] = NULL;

    if (piece == NULL) {
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

uint Board::promote() {
    uint promoted = 0;
    for (uint x = 0; x < size; x++) {
        //First row
        Piece* piece = this->board[x][0];
        if (piece != NULL && piece->getColor() == Color::BLACK && piece->getType() == PieceType::MAN) {
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
    uint x = xy.getX();
    uint y = xy.getY();
    uint targetX = targetXY.getX();
    uint targetY = targetXY.getY();
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
    uint val = abs(xMovement) + abs(yMovement);
    Piece* targetPiece = this->board[targetX][targetY];
    Piece* piece = this->board[x][y];
    if (piece == NULL) {
        return false;
    }
    //Man pieces can only advance one diagonal
    if (piece->getType() == PieceType::MAN && val != 2) {
        return false;
    } else if (piece->getType() == PieceType::KING && xMovementModulus != yMovementModulus) {
        return false;
    }
    uint color = piece->getColor();
    if (targetPiece == NULL) {
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

        this->board[x][y] = NULL;
        this->board[targetX][targetY] = piece;
        return true;
    } else if (targetPiece->getColor() == piece->getColor()) {
        return false;
    } else {
        //The "next" position should be blank in order to perform a kill
        uint blankX = x + xMovement + (xMovement>0?1:-1);
        uint blankY = y + yMovement + (yMovement>0?1:-1);
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
            this->board[x][y] = NULL;
            return true;
        } else {
            return false;
        }
    }
}

vector<XY> Board::verifyAdjacentKills(XY xy) const {
    Piece* piece = getPiece(xy);
    vector<XY> positions;
    if (piece == 0) {
        return positions;
    }

    uint type = piece->getType();
    uint color = piece->getColor();

    XY pos;

    //Man verification
    if (type == PieceType::MAN) {
        //Upper color
        if (color == Color::WHITE) {
            pos = xy.plus(1, 1);
            if (verifyKill(xy, pos)) {
                positions.push_back(pos);
            }
            pos = xy.plus(-1, 1);
            if (verifyKill(xy, pos)) {
                positions.push_back(pos);
            }
        } else {
            pos = xy.plus(1, -1);
            if (verifyKill(xy, pos)) {
                positions.push_back(pos);
            }
            pos = xy.plus(-1, -1);
            if (verifyKill(xy, pos)) {
                positions.push_back(pos);
            }
        }
    }//King
    else {
        uint size = getSize();
        //The shortest kill will have a movement length of 1
        //The longest kill will have a movement length of size-2
        for (uint i = 1; i < size - 1; i++) {
            //Check all directions
            for (uint direction = 0; direction < 4; direction++) {
                switch (direction) {
                        //(+1,+1)
                    case 0:
                        pos = xy.plus(i, i);
                        break;
                        //(+1,-1)
                    case 1:
                        pos = xy.plus(i, -i);
                        break;
                        //(-1,+1)
                    case 2:
                        pos = xy.plus(-i, i);
                        break;
                        //(-1,-1)
                    case 3:
                        pos = xy.plus(-i, -i);
                        break;
                }
                if (pos > size - 1) continue;
                if (verifyKill(xy, pos)) {
                    positions.push_back(pos);
                }
            }
        }
    }
    return positions;
}

bool Board::verifyKill(XY xy, XY targetXY) const {
    uint max = size - 1;
    uint x = xy.getX();
    uint y = xy.getY();
    uint targetX = targetXY.getX();
    uint targetY = targetXY.getY();
    if (x > max || y > max || targetX > max || targetY > max) {
        return false;
    }

    Piece* piece = getPiece(xy);
    Piece* targetPiece = getPiece(targetXY);
    int xMovement = targetX - x;
    int yMovement = targetY - y;
    uint blankX = xMovement + (xMovement > 0 ? 1 : -1) + x;
    uint blankY = yMovement + (yMovement > 0 ? 1 : -1) + y;
    if (blankX > max || blankY > max) {
        return false;
    }
    XY blank(blankX, blankY);
    if (piece == NULL || targetPiece == NULL) {
        return false;
    }
    if (piece->getColor() == targetPiece->getColor()) {
        return false;
    }
    return !hasPiece(blank);
}

uint Board::verifyPossibleKills(uint playerColor, map<XY, vector<XY> >& possibleKills, vector<XY>& piecesXY) const {
    uint possibleKillsCount = 0;

    for (uint x = 0; x < size; x++) {
        for (uint y = 0; y < size; y++) {
            XY xy(x, y);
            Piece* piece = getPiece(xy);
            if (piece != NULL && piece->getColor() == playerColor) {
                vector<XY> poss = verifyAdjacentKills(xy);
                possibleKillsCount += poss.size();
                possibleKills[xy] = poss;
                if (poss.size() > 0) {
                    piecesXY.push_back(xy);
                }
            }
        }
    }
    
    for (int i = 0; i < piecesXY.size(); i++) {
        const XY& xy = piecesXY[i];
        if (possibleKills[xy].size() == 0) {
            possibleKills.erase(xy);
        }
    }
    
    return possibleKillsCount;
}


