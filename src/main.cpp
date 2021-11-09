#include "ai.cpp"
#include "board.cpp"
#include <iostream>

using namespace std;

void game(Board &board, Mode &A, Mode &B, ulong &MCTS){
    short white = 1;
    short black = 2;

  cout << "--\n";
  board.debugout();
    while(true){
        cout << "--\n";
        if (not board.has_lost(white)){
          alpha_beta_get_move(board, A);
          cout << "White's turn:\n";
          board.debugout();
          board.whites_turn = false;

        }else{
          cout << "Black won;";
          board.debugout();
          return;
        }

        if (not board.has_lost(black)){
          alpha_beta_get_move(board, B);
          cout << "Black's turn:\n";
          board.debugout();
          board.whites_turn = true;


        }else{
          cout << "White won;";
          board.debugout();
          return;
        }
    }    

}

int main(int argc, char const *argv[])
{
  /* code */
  Board gameboard = Board();
  Mode player_a(a_b_mobility);
  Mode player_b(a_b_mobility);
  ulong MCTS = 10000;
  game(gameboard, player_a, player_b, MCTS);
  return 0;
}

