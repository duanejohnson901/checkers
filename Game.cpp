#include "Game.h"

Game::Game(int mode, int boardSize, int startingPlayerColor) {
    this->mode = mode;
    this->board = new Board(boardSize);
    this->drawer = new ConsoleDrawer();
    this->io = new ConsoleIO();
    this->ended = false;
    this->currentPlayerColor = startingPlayerColor;
    this->turn = 1;

    switch (this->mode) {
        case GameMode::AI_VS_AI:
            this->whitePlayer = new AI(PieceColor::WHITE, this->board);
            this->blackPlayer = new AI(PieceColor::BLACK, this->board);
            break;
        case GameMode::PLAYER_VS_PLAYER:
            this->whitePlayer = new Human(PieceColor::WHITE, this->board, this->io);
            this->blackPlayer = new Human(PieceColor::BLACK, this->board, this->io);
            break;
        case GameMode::PLAYER_VS_AI:
            this->whitePlayer = new Human(PieceColor::WHITE, this->board, this->io);
            this->blackPlayer = new AI(PieceColor::BLACK, this->board);
            break;
    }
}

Game::~Game() {
    delete this->drawer;
    delete this->io;
    delete this->whitePlayer;
    delete this->blackPlayer;

    int size = this->board->getSize();

    int deleted = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Piece* piece = this->board->getPiece(XY(i, j));
            if (piece != 0) {
                delete piece;
                deleted++;
            }
        }
    }
    delete this->board;
    cout << deleted << " pieces deleted";
}

void Game::newGame() {
    board->init();
    start();
}

void Game::start() {
    bool playAgain = false;
    while (!this->ended) {
        this->drawer->clear();
        this->drawer->drawInfo(this->turn, this->currentPlayerColor, board->getWhiteCount(), board->getBlackCount());
        this->drawer->drawBoard(this->board);

        if (this->board->getBlackCount() == 0) {
            this->io->message("White wins!\n");
            this->ended = true;
            break;
        } else if (this->board->getWhiteCount() == 0) {
            this->io->message("Black wins!\n");
            this->ended = true;
            break;
        }

        //Check every piece to verify possible kills
        map<XY, vector<XY> > possibleKills;

        vector<XY> piecesXY;

        int size = board->getSize();
        int possibleKillsCount = 0;

        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                XY xy(x, y);
                Piece* piece = board->getPiece(xy);
                if (piece != 0 && piece->getColor() == currentPlayerColor) {
                    vector<XY> poss = verifyAdjacentKills(xy);
                    possibleKillsCount += poss.size();
                    possibleKills[xy] = poss;
                    if (poss.size() > 0) {
                        piecesXY.push_back(xy);
                    }
                }
            }
        }
        ostringstream out;
        out << "Possible kills: " << possibleKillsCount << "\n";
        this->io->message(out.str());

        bool played = false;
        Player* player = 0;
        if (this->currentPlayerColor == PieceColor::WHITE) {
            player = this->whitePlayer;
        } else {
            player = this->blackPlayer;
        }
        if (possibleKillsCount > 0) {
            XY piecePosition = player->chooseKillPiece(piecesXY);
            XY targetPosition = player->chooseKillTarget(possibleKills[piecePosition]);
            board->movePiece(piecePosition, targetPosition);
            played = true;
            playAgain = true;
        }
            //The user is playing the second round, but there are no more possible kills (for combo kill), so the turn must end
        else if (playAgain) {
            played = true;
            playAgain = false;
        } else {
            played = player->play();
        }
        //Only change the turn if the player is not supposed to play again
        if (played && !playAgain) {
            this->currentPlayerColor = this->currentPlayerColor == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
            this->turn++;
        }
        this->board->promote();
        this->io->pause();
    }
    this->io->pause();
}

vector<XY> Game::verifyAdjacentKills(XY xy) {
    Piece* piece = board->getPiece(xy);
    vector<XY> positions;
    if (piece == 0) {
        return positions;
    }

    int type = piece->getType();
    int color = piece->getColor();

    XY pos;

    //Man verification
    if (type == PieceType::MAN) {
        //Upper color
        if (color == PieceColor::WHITE) {
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
    }        
    //King
    else {
        int size = board->getSize();
        //The shortest kill will have a movement length of 1
        //The longest kill will have a movement length of size-2
        for (int i = 1; i < size - 1; i++) {
            //Check all directions
            for (int direction = 0; direction < 4; direction++) {
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
                if (pos < 0 || pos > size - 1) continue;
                if (verifyKill(xy, pos)) {
                    positions.push_back(pos);
                }
            }
        }
    }
    return positions;
}

bool Game::verifyKill(XY xy, XY targetXY) {
    int max = board->getSize() - 1;
    int x = xy.getX();
    int y = xy.getY();
    int targetX = targetXY.getX();
    int targetY = targetXY.getY();
    if (x < 0 || y < 0 || targetX < 0 || targetY < 0 || x > max || y > max || targetX > max || targetY > max) {
        return false;
    }

    Piece* piece = board->getPiece(xy);
    Piece* targetPiece = board->getPiece(targetXY);
    int xMovement = targetX - x;
    int yMovement = targetY - y;
    int blankX = xMovement + (xMovement > 0 ? 1 : -1) + x;
    int blankY = yMovement + (yMovement > 0 ? 1 : -1) + y;
    if (blankX > max || blankY > max || blankX < 0 || blankY < 0) {
        return false;
    }
    XY blank(blankX, blankY);
    if (piece == 0 || targetPiece == 0) {
        return false;
    }
    if (piece->getColor() == targetPiece->getColor()) {
        return false;
    }
    return !board->hasPiece(blank);
}

void Game::save(const char* filename) {

}

void Game::load(const char* filename) {
    vector<string> data;
    data.push_back("0 0 0 0 0 0 0 0");
    data.push_back("0 0 0 0 0 0 0 0");
    data.push_back("0 A A 0 8 0 8 0");
    data.push_back("0 0 0 @ 0 8 0 0");
    data.push_back("0 0 0 0 8 0 8 0");
    data.push_back("0 0 0 0 0 0 0 0");
    data.push_back("0 0 0 0 0 0 0 0");
    data.push_back("0 0 0 0 0 0 0 0");
    board->load(data);
    start();
}