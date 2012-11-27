#ifndef XY_H
#define XY_H

#include "Types.h"

/**
 * XY class
 * Simple class for storing 2D coordinates
 */
class XY {
private:
    uint x;
    uint y;
public:
    
    XY() {
        this->x = this->y = 0;
    }

    XY(uint x, uint y) {
        this->x = x;
        this->y = y;
    }

    uint getX() const {
        return x;
    }

    uint getY() const {
        return y;
    }

    /**
     * Returns a new coordinate with x and y incremented by the x and y parameters
     * @param x
     * @param y
     * @return 
     */
    XY plus(uint x, uint y) const {
        return XY(this->x + x, this->y + y);
    }

    bool operator<(const XY& other) const {
        return x == other.x ? y < other.y : x < other.x;
    }

    bool operator<(const uint val) const {
        return x < val || y < val;
    }

    bool operator>(const uint val) const {
        return x > val || y > val;
    }

    bool operator>=(const uint val) const {
        return x >= val || y >= val;
    }

    bool operator<=(const uint val) const {
        return x <= val || y <= val;
    }
    
};

#endif