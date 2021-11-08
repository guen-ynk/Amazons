#pragma once
#include "board.hpp"
/**
 * @brief 
 *      entrance function for alphabeta prunning,
 *      chooses the best move for wturn as the maximizing player and performs it.
        currently using the following optimizations:
            -   depth = 6 not 2 for the endgame ( #possible moves < 15)
            -   cutoffs
            -   *not anymore* randomized playorder 
            -   move and undo move -> using only the original board not wasting space
        open ideas:
            -   move ordering
            -   multithreading for calling instance of AB -> buying time for space
 * 
 * @param board The board object
 *       see board.hpp
 * @param mode The Heuristic
 *       see board.hpp. In this scope only possible
 *              a_b_mobility 
 *              a_b_territorial 
 */
void alpha_beta_get_move(Board &board, Mode &mode);
/**
 * @brief 
 *       function for alphabeta prunning
 * @param board board obj
 * @param depth depth of current iteration 
 * @param a     ALPHA
 * @param b     BETA
 * @param calling_player stores the bool value of calling player 
 * @param whites_turn current player bool
 * @param mode        heuristic 
 * @return _Float32, the alphabeta values for the calling AB instance
 */

_Float32 alpha_beta(Board &board, u_short  &depth, _Float32 &a, _Float32 &b, const bool &calling_player, bool whites_turn, const Mode &mode);