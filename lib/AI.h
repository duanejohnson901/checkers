#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Random.h"
#include "Types.h"

#include <algorithm>
#include <map>

using namespace std;

const int MAX_DEPTH = 100;

/**
 * AI class
 * Subclass player and provides an AI implementation
 */
class AI : public Player {
private:
    //The level of the AI from 1 to 9 (@see AILevel)
    uint level;    
    //Constrols the depth of the recursion
    mutable uint depth;
public:
    AI() = delete;
    AI(uint color, Board& board, IO& io, uint aiLevel);
    bool play();
    XY chooseKillPiece(const vector<XY>& killPositions, const map<XY, vector<XY> >& possibleKills) const;
    XY chooseKillTarget(const vector<XY>& targetPositions) const;
    uint getType() const { return PlayerType::AI; }
    //AI methods
    /**
     * Verifies the given board and stablishes a value to int
     * Higher values are better for the player
     * Each possible kill increments by one the board value
     * Each opponent possible kill decrements by one the board value
     * Multiple kills are NOT evaluated yet (future implementation)
     * @param board The board to verified
     * @return 
     */
    int determineBoardValue(const Board& targetBoard) const;
    
    map<int, XY> chooseBestKillPiece(const Board& targetBoard, const vector<XY>& killPositions, const map<XY, vector<XY> >& possibleKills) const;
    //map<int, XY&> chooseBestKillTarget(const Board& board, const vector<XY>& killPositions, const map<XY, vector<XY> >& possibleKills) const;

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