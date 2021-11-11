#pragma once
#include "board.hpp"

struct formula{
    _Float32 w1,w2,w3,w4,c1,c2,t1,t2,p,q = 0.0;
};

_Float32 mobility_evaluation(Board &board, short &token);


void init_formula(Board &board, formula &eval);

void bfs(Board &board, Coordinates &pos, Matrix<short,Dynamic,Dynamic> &heuristic_board, bool mode);

vector<Coordinates> queen_moves(Board &board, size_t depth, Matrix<short,Dynamic,Dynamic> &heuristic_board,Coordinates &c);

vector<Coordinates> king_moves(Board &board, size_t depth, Matrix<short,Dynamic,Dynamic> &heuristic_board,Coordinates &c);

void calculate_t_p_heuristic(Board &board, short &token, formula &eval);

_Float32 territorial_positional_evaluation(Board &board, short &token);
