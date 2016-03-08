#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {
private:
	Board board, shadowBoard;
	Side p_side, op_side;
public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);


    float heuristic(Move *move);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
