#include "../lib/Game.h"

Game::Game(const string& loadFileName) {
    ifstream infile(loadFileName.c_str());
    vector<string> boardData;
    string line;
    //line counter
    uint i = 0;
    //board size
    uint boardSize = 0;
    if (!infile.good()) {
        throw new invalid_argument("Invalid file");
    }
    try {
        while (getline(infile, line)) {
            istringstream is(line, istringstream::in);
            switch (i){
                //First line is for game mode number
                case 0:
                    is >> mode;
                    break;
                //Second line is for turn number
                case 1:
                    is >> turn;
                    break;
                //Third line is for the board size
                case 2:
                    is >> boardSize;
                    break;
                //Forth line is for the current player color number
                case 3:
                    is >> currentPlayerColor;
                    break;
                //Fifth line is for the AI level
                case 4:
                    is >> aiLevel;
                    break;
                //Other lines are for the board
                default:
                    if (line.length() < boardSize*2-1) {
                        //Invalid file
                        throw new invalid_argument("Invalid game file: incorrect board line length");
                    }
                    boardData.push_back(line);
            }
            i++;
        }
    } catch (const exception& ex) {
        throw new invalid_argument("Invalid game file");
    }
    board = new Board(boardSize);
    board->load(boardData);   
    drawer = new ConsoleDrawer();
    io = new ConsoleIO();
    initMode();
}

Game::Game(uint mode, uint boardSize, uint startingPlayerColor, uint aiLevel) {
    if (aiLevel > AILevel::HARDEST || aiLevel < AILevel::EASIEST) {
        throw new invalid_argument("Invalid AI Level");
    } 
    if (mode != GameMode::AI_VS_AI && mode != GameMode::PLAYER_VS_AI && mode != GameMode::PLAYER_VS_PLAYER) {
        throw new invalid_argument("Invalid Game Mode");
    }
    if (startingPlayerColor != Color::WHITE && startingPlayerColor != Color::BLACK) {
        throw new invalid_argument("Invalid starting player color");
    }
    if (boardSize > MAX_BOARD_SIZE) {
        throw new invalid_argument("Invalid board size");
    }
    this->mode = mode;
    this->aiLevel = aiLevel;
    this->board = new Board(boardSize);
    this->drawer = new ConsoleDrawer();
    this->io = new ConsoleIO();
    this->ended = false;
    this->currentPlayerColor = startingPlayerColor;
    this->turn = 1;
    initMode();
    newGame();
}

void Game::initMode() {
    switch (this->mode) {
        case GameMode::AI_VS_AI:
            this->whitePlayer = new AI(Color::WHITE, *board, *io, aiLevel);
            this->blackPlayer = new AI(Color::BLACK, *board, *io, aiLevel);
            break;
        case GameMode::PLAYER_VS_PLAYER:
            this->whitePlayer = new Human(Color::WHITE, *board, *io);
            this->blackPlayer = new Human(Color::BLACK, *board, *io);
            break;
        case GameMode::PLAYER_VS_AI:
            this->whitePlayer = new Human(Color::WHITE, *board, *io);
            this->blackPlayer = new AI(Color::BLACK, *board, *io, aiLevel);
            break;
    }
}

Game::~Game() {
    delete this->drawer;
    delete this->io;
    delete this->whitePlayer;
    delete this->blackPlayer;
    delete this->board;
}

void Game::newGame() {
    board->init();
}

void Game::start() {
    bool playAgain = false;
    while (!this->ended) {
        this->drawer->clear();
        this->drawer->drawInfo(this->turn, this->currentPlayerColor, board->getWhiteCount(), board->getBlackCount());
        this->drawer->drawBoard(*this->board);

        if (this->board->getBlackCount() == 0) {
            this->io->message("White wins!\n");
            this->ended = true;
            break;
        } else if (this->board->getWhiteCount() == 0) {
            this->io->message("Black wins!\n");
            this->ended = true;
            break;
        }
        
        Player* player = 0;
        if (this->currentPlayerColor == Color::WHITE) {
            player = this->whitePlayer;
        } else {
            player = this->blackPlayer;
        }
        //Verify if it's a human player and shows the menu
        if (player->getType() == PlayerType::HUMAN) {
            if (!menu()) {
                break;
            }
        }
        
        //Check every piece to verify possible kills
        map<XY, vector<XY> > possibleKills;
        vector<XY> piecesXY;
        int possibleKillsCount = board->verifyPossibleKills(currentPlayerColor, possibleKills, piecesXY);
        
        ostringstream out;
        out << "Possible kills: " << possibleKillsCount << "\n";
        this->io->message(out.str());

        bool played = false;
        if (possibleKillsCount > 0) {
            if (possibleKills.size() <= 0 || piecesXY.size() <= 0) {
                //This should not happen
                throw new exception;
            }
            XY piecePosition = player->chooseKillPiece(piecesXY, possibleKills);
            XY targetPosition = player->chooseKillTarget(possibleKills[piecePosition]);
            board->movePiece(piecePosition, targetPosition);
            played = true;
            playAgain = true;
        }//The user is playing the second round, but there are no more possible kills (for combo kill), so the turn must end
        else if (playAgain) {
            played = true;
            playAgain = false;
        } else {
            played = player->play();
        }
        //Only change the turn if the player is not supposed to play again
        if (played && !playAgain) {
            this->currentPlayerColor = this->currentPlayerColor == Color::WHITE ? Color::BLACK : Color::WHITE;
            this->turn++;
        }
        this->board->promote();
        if (player->getType() == PlayerType::AI) {
            Sleep(10);
        } else {
            this->io->pause();
        }
    }
    this->io->pause();
}

bool Game::menu() {
    //Prints the menu
    io->message("# Menu # Choose an option: #\n");
    io->message("1 - Play\n");
    io->message("2 - Save\n");
    io->message("3 - Quit\n: ");
    uint option = 0;
    do {
        option = io->getInt();
    }
    while (option < 1 || option > 3);
    switch (option) {
        case 2: {
            io->message("Enter the name of the file: \n");
            const string fileName = io->getString();
            save(fileName);
            return true;
        }
        case 3: {
            ended = true;
            return false;
        }
    }
    return true;
}

void Game::save(const string& fileName) {
    ofstream outfile(fileName.c_str());
    
    if(!outfile) {
        io->message("Cannot open the output file.");
    } else {
        uint size = board->getSize();
        outfile << mode << "\n";
        outfile << turn << "\n";
        outfile << size << "\n";
        outfile << currentPlayerColor << "\n";
        Piece* piece = NULL;
        for (uint y = 0; y < size; y++) {
            for (uint x = 0; x < size; x++) {
                piece = board->getPiece(XY(x,y));
                if (piece == NULL) {
                    outfile << BLANK_CHAR;
                } else {
                    uint type = piece->getType();
                    uint color = piece->getColor();
                    if (type == PieceType::KING) {
                        outfile << (color==Color::WHITE? WHITE_KING_CHAR: BLACK_KING_CHAR);
                    } else {
                        outfile << (color==Color::WHITE? WHITE_MAN_CHAR: BLACK_MAN_CHAR);
                    }
                }
                outfile << " ";
            }
            outfile << "\n";
        }
        outfile.flush();
        outfile.close();
        io->message("Game saved successfully.\n");
    }
}

