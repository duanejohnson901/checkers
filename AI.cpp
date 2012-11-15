#include <stdlib.h>

#include "AI.h"

AI::AI(int color, Board* board, IO* io) : Player(color, board, io) {
}

bool AI::play() {
    //Search for all piece
    vector<XY> piecesPosition;
    vector<Piece*> pieces;
    int size = board->getSize();
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            XY xy(x, y);
            Piece* piece = board->getPiece(xy);
            if (piece != 0 && piece->getColor() == color) {
                piecesPosition.push_back(xy);
                pieces.push_back(piece);
            }
        }
    }

    //Choose the first piece that can do any movement
    vector<int> numbers;
    while (true) {
        int i = Random::get(pieces.size() - 1);
        if (find(numbers.begin(), numbers.end(), i) != numbers.end()) {
            io->message("@");
            continue;
        }
        numbers.push_back(i);

        Piece* piece = pieces[i];
        XY xy = piecesPosition[i];

        int color = piece->getColor();
        int type = piece->getType();

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
                    case PieceColor::WHITE:
                        movements.push_back(xy.plus(1, 1));
                        movements.push_back(xy.plus(-1, 1));
                        break;
                    case PieceColor::BLACK:
                        movements.push_back(xy.plus(1, -1));
                        movements.push_back(xy.plus(-1, -1));
                        break;
                }
        }
        while (!movements.empty()) {
            XY target = movements.back();
            if (target.getX() > 0 && target.getY() > 0 &&
                    target.getX() < size && target.getY() < size &&
                    !board->hasPiece(target)) {
                if (board->movePiece(xy, target)) {
                    return true;
                } else {
                    return false;
                }
            }
            movements.pop_back();
            io->message(".");
        }
    }
    return true;
}

XY AI::chooseKillPiece(vector<XY>& killPositions) {
    return killPositions[Random::get(killPositions.size() - 1)];
}

XY AI::chooseKillTarget(vector<XY>& targetPositions) {
    return targetPositions[Random::get(targetPositions.size() - 1)];
}
