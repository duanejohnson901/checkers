#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "IO.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

/**
 * ConsoleIO class
 * Uses the standard IO to interact with the user
 */
class ConsoleIO : public IO {
public:
    /**
     * Calls system("pause")
     */
    void pause() const;
    XY getMovementPiece() const;
    XY getMovementTarget() const;
    XY choosePosition(const vector<XY>& positions) const;
    void message(const string& message) const;
    int getInt() const;
    string getString() const;
};

#endif