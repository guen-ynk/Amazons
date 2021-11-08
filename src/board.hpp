// sample.h
#pragma once
#include <vector> // #include directive
#include <iostream>

#include "Eigen/Dense"
#include "move.cpp"

#define iterv(x) for (int i=0; i<=(x.size()); i++)
#define iterv_inner(x) for (int j=0; j<=(x.size()); j++)

#define move_s(in) (in.s.x, in.s.y) 
#define move_d(in) (in.d.x, in.d.y) 
#define move_a(in) (in.a.x, in.a.y) 

#define move_ind(in) (in.x,in.y)

using namespace std;
using namespace Eigen;

enum Mode {human, a_b_mobility, a_b_territorial, mcts_vanilla, mcts_optimized};
class Board {
    public:
        bool whites_turn;
        short board_size;
        short amazons_count;
        Matrix<short,Dynamic,Dynamic> field;

        vector<Coordinates> operations {
            Coordinates(1,0),Coordinates(-1,0),Coordinates(0,1),Coordinates(0,-1),
            Coordinates(1,1),Coordinates(1,-1),Coordinates(-1,1),Coordinates(-1,-1)
        };

        
        Board();

        /*
            returns vector of coordinates ( amazons )
        **/
        vector<Coordinates> get_queen_positions(short &color);
         /*
            returns vector of coordinates ( reachable for amazon at position c )
        **/
        vector<Coordinates> get_amazon_moves(Coordinates &c);
        /*
            returns whether the player of corresponding color has lost the Game i.o.w. if noone of colors Amazons can be moved
        **/
        bool has_lost(short &color); 
        /*
            returns vector of MOVES 
        **/
        vector<Move> generate_moves(short &color);

        void debugout();
};


 