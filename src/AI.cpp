#include <stdlib.h>

#include "../lib/AI.h"

AI::AI(uint color, Board& board, IO& io, uint level) : Player(color, board, io) {
    this->level = level;
}

bool AI::play() {
    //Search for all pieces
    vector<XY> piecesPosition;
    vector<Piece*> pieces;
    uint size = board.getSize();
    for (uint x = 0; x < size; x++) {
        for (uint y = 0; y < size; y++) {
            XY xy(x, y);
            Piece* piece = board.getPiece(xy);
            if (piece != 0 && piece->getColor() == color) {
                piecesPosition.push_back(xy);
                pieces.push_back(piece);
            }
        }
    }

    //Choose the first piece that can do any movement
    vector<int> numbers;
    while (true) {
        uint i = Random::get(0, pieces.size() - 1);
        if (pieces.size() == 1) {
            i = 0;
        } else if (find(numbers.begin(), numbers.end(), i) != numbers.end()) {
            io.message(".");
            continue;
        }
        numbers.push_back(i);

        Piece* piece = pieces[i];
        XY xy = piecesPosition[i];

        uint color = piece->getColor();
        uint type = piece->getType();

        vector<XY> movements;
        switch (type) {
            case PieceType::KING:
                movements.push_back(xy.plus(1, 1));
                movements.push_back(xy.plus(-1, 1));
                movements.push_back(xy.plus(1, -1));
                movements.push_back(xy.plus(-1, -1));
                break;
            case PieceType::MAN:
                switch (color) {
                    case Color::WHITE:
                        movements.push_back(xy.plus(1, 1));
                        movements.push_back(xy.plus(-1, 1));
                        break;
                    case Color::BLACK:
                        movements.push_back(xy.plus(1, -1));
                        movements.push_back(xy.plus(-1, -1));
                        break;
                }
        }
        while (!movements.empty()) {
            XY target = movements.back();
            if (target.getX() >= 0 && target.getY() >= 0 &&
                    target.getX() < size && target.getY() < size &&
                    !board.hasPiece(target)) {
                if (board.movePiece(xy, target)) {
                    return true;
                } else {
                    return false;
                }
            }
            movements.pop_back();
            io.message(".");
        }
    }
    return true;
}

map<int, XY> AI::chooseBestKillPiece(const Board& targetBoard, const vector<XY>& killPositions, const map<XY, vector<XY> >& possibleKills) const {
    map<int, XY> boardValues;
    //Check if the maximum recursion depth has been reached
    if (depth == MAX_DEPTH) {
        return boardValues;
    }
    for (int i = 0; i < killPositions.size(); i++) {
        //Make a copy of the board
        Board boardCopy = targetBoard;
        const XY& xy = killPositions[i];
        //Verify all possible kills for the selected kill piece
        vector<XY> kills = possibleKills.at(xy);
        for (int j = 0; j < kills.size(); j++) {
            const XY& targetXY = kills[j];
            if (!boardCopy.movePiece(xy, targetXY)) {
                //This should not happen
                throw new exception;
            }
            int value = determineBoardValue(boardCopy);
            boardValues[value] = xy;
        }
    }
    depth++;
    return boardValues;
}

XY AI::chooseKillPiece(const vector<XY>& killPositions, const map<XY, vector<XY> >& possibleKills) const {
    switch (level) {
        default:
            map<int, XY> boardValues = chooseBestKillPiece(board, killPositions, possibleKills);
            int highestValue = boardValues.rbegin()->first;
            return boardValues[highestValue];
    }
}

XY AI::chooseKillTarget(const vector<XY>& targetPositions) const {
    //Board map
    switch (level) {
        default:
            return targetPositions[Random::get(0, targetPositions.size() - 1)];
    }
}

int AI::determineBoardValue(const Board& targetBoard) const {
    map<XY, vector<XY> > possibleKills;
    vector<XY> piecesXY;
    switch (level) {
        default:
        {
            int playerPossibleKills = targetBoard.verifyPossibleKills(color, possibleKills, piecesXY);
            int opponentPossibleKills = targetBoard.verifyPossibleKills(color == Color::BLACK ? Color::WHITE : Color::BLACK, possibleKills, piecesXY);
            return playerPossibleKills - opponentPossibleKills;
        }
    }
}
