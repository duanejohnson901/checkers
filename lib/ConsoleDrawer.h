#ifndef CONSOLE_DRAWER_H
#define CONSOLE_DRAWER_H

#include "Drawer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class ConsoleDrawer : public Drawer {
public:
    void clear();
    void drawInfo(int turn, int currentPlayerColor, int whitePieces, int blackPieces);
    void drawBoard(Board *board);
};

#endif