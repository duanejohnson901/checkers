#include "../lib/ConsoleDrawer.h"

void ConsoleDrawer::clear() const {
    system("cls");
}

void ConsoleDrawer::drawInfo(int turn, int currentPlayerColor, int whitePieces, int blackPieces) const {
    cout << "Turn: " << turn << "\n";
    cout << "Current Player: " << (currentPlayerColor == Color::WHITE ? "White (A/@) " : "Black (8/&)") << "\n";
    cout << "White Pieces: " << whitePieces << "\n";
    cout << "Black Pieces: " << blackPieces << "\n";
}

void ConsoleDrawer::drawBoard(const Board& board) const{
    int size = board.getSize();
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "    ";
            for (int j = 0; j < size; j++) {
                cout << " " << j << "  ";
            }
            cout << "\n   |";
        } else {
            cout << "   |";
        }
        for (int j = 0; j < size; j++) {
            cout << "---|";
        }
        cout << "\n " << i << " |";
        for (int j = 0; j < size; j++) {
            Piece* piece = board.getPiece(XY(j, i));
            char pieceChar = BLANK_CHAR;
            if (piece != 0) {
                int type = piece->getType();
                int color = piece->getColor();
                if (color == Color::WHITE) {
                    pieceChar = type == PieceType::MAN ? WHITE_MAN_CHAR : WHITE_KING_CHAR;
                } else {
                    pieceChar = type == PieceType::MAN ? BLACK_MAN_CHAR : BLACK_KING_CHAR;
                }
            }

            cout << " " << pieceChar << " |";
        }

        if (i == size - 1) {
            cout << "\n   |";
            for (int j = 0; j < size; j++) {
                cout << "---|";
            }
        }

        cout << "\n";
    }
}