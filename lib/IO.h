#ifndef IO_H
#define IO_H

#include "XY.h"

#include <vector>
#include <string>

using namespace std;

//Game Input

class IO {
public:
    virtual void pause() const = 0;
    virtual XY getMovementPiece() const = 0;
    virtual XY getMovementTarget() const = 0;
    virtual XY choosePosition(const vector<XY>& positions) const = 0;
    virtual void message(const char* message) const = 0;
    virtual void message(string message) const = 0;
};

#endif