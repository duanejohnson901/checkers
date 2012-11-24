#ifndef CONSOLE_DRAWER_H
#define CONSOLE_DRAWER_H

#include "Drawer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * ConsoleDrawer class
 * Draws the game into a console window
 */
class ConsoleDrawer : public Drawer {
public:
    void clear() const;
    void drawInfo(int turn, int currentPlayerColor, int whitePieces, int blackPieces) const;
    void drawBoard(const Board& board) const;
};

#endif