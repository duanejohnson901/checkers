#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Random.h"
#include "Types.h"
#include <algorithm>

using namespace std;

/**
 * AI class
 * Subclass player and provides an AI implementation
 */
class AI : public Player {
private:
    //The level of the AI from 1 to 9 (@see AILevel)
    uint level;
public:
    AI() = delete;
    AI(uint color, Board& board, IO& io, uint aiLevel);
    bool play();
    XY chooseKillPiece(const vector<XY>& killPositions) const;
    XY chooseKillTarget(const vector<XY>& targetPositions) const;
    uint getType() const { return PlayerType::AI; }
};

/**
 * AILevel enum
 */
namespace AILevel {
    enum {
        EASIEST = 1,
        EASIER = 2,
        EASY = 3,
        ALMOST_EASY = 4,
        MEDIUM = 5,
        ALMOST_HARD = 6,
        HARD = 7,
        HARDER = 8,
        HARDEST = 9
    };
};

#endif