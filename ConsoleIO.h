#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IO.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

class ConsoleIO : public IO {
public:
    void pause();
    XY getMovementPiece();
    XY getMovementTarget();
    XY choosePosition(vector<XY>& positions);
    void message(const char* message);
    void message(string message);
};

#endif