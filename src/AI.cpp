#include <stdlib.h>

#include "../lib/AI.h"

AI::AI(uint color, Board& board, IO& io, uint level) : Player(color, board, io) {
    this->level = level;
}

bool AI::play() {
    //Search for all piece
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
        if (find(numbers.begin(), numbers.end(), i) != numbers.end()) {
            io.message("@");
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
            if (target.getX() > 0 && target.getY() > 0 &&
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

XY AI::chooseKillPiece(const vector<XY>& killPositions) const {
    switch (level) {
        default:
        return killPositions[Random::get(0, killPositions.size() - 1)];
    }
}

XY AI::chooseKillTarget(const vector<XY>& targetPositions) const {
    switch (level) {
        default:
        return targetPositions[Random::get(0, targetPositions.size() - 1)];
    }
}
