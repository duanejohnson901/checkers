#ifndef IO_H
#define IO_H

#include "XY.h"

#include <vector>
#include <string>

using namespace std;

/**
 * IO class
 * Abstract base class responsible for showing messages and gathering user input
 */
class IO {
public:
    /**
     * Makes a pause and wait for user to press OK/Enter
     */
    virtual void pause() const = 0;
    /**
     * Asks the user the piece he wants to move
     * @return The coordinate of the selected piece
     */
    virtual XY getMovementPiece() const = 0;
    /**
     * Asks the user the coordinates of the target piece/move
     * @return The coordinate selected
     */
    virtual XY getMovementTarget() const = 0;
    /**
     * Asks the user to choose a position from the given list
     * @param positions 
     * @return The position chose
     */
    virtual XY choosePosition(const vector<XY>& positions) const = 0;
    /**
     * Shows a message on the screen
     * @param message The message to be shown
     */
    virtual void message(const string& message) const = 0;
};

#endif