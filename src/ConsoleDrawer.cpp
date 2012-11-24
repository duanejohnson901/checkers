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
    char noPiece = ' ';
    char whiteMan = 'A';
    char whiteKing = '@';
    char blackMan = '8';
    char blackKing = '&';

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
            char pieceChar = noPiece;
            if (piece != 0) {
                int type = piece->getType();
                int color = piece->getColor();
                if (color == Color::WHITE) {
                    pieceChar = type == PieceType::MAN ? whiteMan : whiteKing;
                } else {
                    pieceChar = type == PieceType::MAN ? blackMan : blackKing;
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