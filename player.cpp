#include "player.h"
#define VERSION 1

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
        std::cerr << "WHITE" << std::endl;
    }
    else{
        op_side = WHITE;
        std::cerr << "BLACK" << std::endl;
    }
    std::cerr << VERSION << std::endl;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
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
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    Move candidate(0,0);
    Move *bestCand = NULL;
    float bestHeur = -100000000;
    if(opponentsMove != NULL){
        board.doMove(opponentsMove, op_side);
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            candidate.setX(i);
            candidate.setY(j);
            if(board.checkMove(&candidate, p_side)){
                float heur = heuristic(&candidate);

                if(heur > bestHeur){
                    if(NULL == bestCand){
                        bestCand = new Move(i, j);
                    }
                    else{
                        *bestCand = candidate;
                    }
                   bestHeur = heur;
                }
            }
        }   
    }
    board.doMove(bestCand, p_side);
    return bestCand;
}

float Player::heuristic(Move *move){
    float val = 0;
    shadowBoard = board;
    shadowBoard.doMove(move, p_side);
    Move probe(0,0);
    val = shadowBoard.count(p_side) - shadowBoard.count(op_side);
    if(move->getX() %7 == 0 || move->getY()%7 == 0 ){
        val += 2;
    }
    if(move->getX() %7 == 0 && move->getY()%7 == 0 ){
        val += 2;
    }
    val*=2;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            probe.setX(i);
            probe.setY(i);
            if(shadowBoard.checkMove(&probe, op_side)){
                val -= 0.5;
            }
        }   
    }
    return val;
}