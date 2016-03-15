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
	float alpha, beta;
public:
    Player(Side side);
    ~Player();
    void setBoard(Board *board);
    Move *doMove(Move *opponentsMove, int msLeft);


    float heuristic(Board *shadow_board, Side side);
    float mini_max(Move *best_move, Board *shadow_board, Side side, int max_depth, int msLeft);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
