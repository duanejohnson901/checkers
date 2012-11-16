#ifndef XY_H
#define XY_H

class XY {
private:
    int x;
    int y;
public:

    XY() {
        this->x = this->y = 0;
    }

    XY(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    XY plus(int x, int y) {
        return XY(this->x + x, this->y + y);
    }

    bool operator<(const XY& other) const {
        return x == other.x ? y < other.y : x < other.x;
    }

    bool operator<(const int val) const {
        return x < val || y < val;
    }

    bool operator>(const int val) const {
        return x > val || y > val;
    }

    bool operator>=(const int val) const {
        return x >= val || y >= val;
    }

    bool operator<=(const int val) const {
        return x <= val || y <= val;
    }
};

#endif