#include "player.h"



Side other_side(Side side){
    return (side == WHITE) ? BLACK : WHITE;
}

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    this->p_side = side;
    if(p_side == WHITE){
        op_side = BLACK;
    }
    else{
        op_side = WHITE;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}
void Player::setBoard(Board *board){
    this->board = *board;
}
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    Move *best_move = new Move(0,0);
    board.doMove(opponentsMove, op_side);
    mini_max(best_move, &board, p_side, 2, msLeft);
    if(best_move != NULL && best_move->getX() < 0){ 
        best_move = NULL;
    }
    board.doMove(best_move, p_side);

    return best_move;
}

float Player::heuristic(Board *shadow_board, Side side){
    float val = 0;
    Side opside = other_side(side);
    val = shadow_board->count(side) - shadow_board->count(opside);

    if(testingMinimax){
        return val;
    }

    for(int i = 0; i < 8; i+=7){
        for(int j = 0; j < 8; j+=7){
            if(shadow_board->get(side, i, j)){
                val += 2;
            }
            if(shadow_board->get(opside, i, j)){
                val -= 2;
            }
        }
    }

    val*=2;
    Move probe(0,0);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            probe.setX(i);
            probe.setY(i);
            if(shadowBoard.checkMove(&probe, opside)){
                val -= 0.5;
            }
        }   
    }
    return val;
}

float Player::mini_max(Move *best_move, Board *shadow_board, Side side, int max_depth, int msLeft){
    if(max_depth == 0){
        return heuristic(shadow_board, side);
    }

    if(!(shadow_board->hasMoves(side))){
        best_move->setX(-1);
        return heuristic(shadow_board, side);
    }

    Move candidate(1,0), op_move(0,0);
    int mult = (side == p_side) ? 1 : -1;
    float bestHeur = -1000000;
    Board curr_board;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            candidate.setX(i);
            candidate.setY(j);

            if(shadow_board->checkMove(&candidate, side)){
                curr_board = *shadow_board;
                curr_board.doMove(&candidate, side);

                float heur = mini_max(&op_move, &curr_board, other_side(side), max_depth - 1, msLeft);
                if(mult * heur > bestHeur){
                    *best_move = candidate;
                    bestHeur = heur;
                }
            }
        }   
    }
    return bestHeur;
}