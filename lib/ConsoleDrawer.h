#ifndef CONSOLE_DRAWER_H
#define CONSOLE_DRAWER_H

#include "Drawer.h"
#include "Types.h"
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
    void drawInfo(uint turn, uint currentPlayerColor, uint whitePieces, uint blackPieces) const;
    void drawBoard(const Board& board) const;
};

#endif