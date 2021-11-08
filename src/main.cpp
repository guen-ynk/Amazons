#include "ai.hpp"
#include "board.cpp"
#include <iostream>

using namespace std;

void game(Board &board, Mode &A, Mode &B, ulong &MCTS){
    board.debugout();

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

