#ifndef IO_H
#define IO_H

#include "XY.h"

#include <vector>
#include <string>

using namespace std;

//Game Input

class IO {
public:
    virtual void pause() = 0;
    virtual XY getMovementPiece() = 0;
    virtual XY getMovementTarget() = 0;
    virtual XY choosePosition(vector<XY>& positions) = 0;
    virtual void message(const char* message) = 0;
    virtual void message(string message) = 0;
};

#endif