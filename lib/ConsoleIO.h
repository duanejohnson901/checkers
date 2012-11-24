#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IO.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

class ConsoleIO : public IO {
public:
    void pause() const;
    XY getMovementPiece() const;
    XY getMovementTarget() const;
    XY choosePosition(const vector<XY>& positions) const;
    void message(const char* message) const;
    void message(string message) const;
};

#endif