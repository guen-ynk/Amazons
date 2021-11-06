#include "board.hpp"

#include <vector>
#include <string>
 


using namespace std;
using namespace Eigen;
 
  
int main(int argc, char const *argv[])
{
    Board board1 = Board();
    
    cout << "field =" << endl << board1.field << endl;
    auto positions = board1.get_amazon_moves(Coordinates(3,9));
    for (size_t i = 0; i < positions.size(); i++)
    {
        cout << positions[i].x << positions[i].y << endl;
        board1.field(positions[i].x,positions[i].y) = 4;
    }
    cout << "field =" << endl << board1.field << endl;
    cout << "lost?" << board1.has_lost(1) << "\n";
    auto moves = board1.generate_moves(1);
    for (size_t i = 0; i < moves.size(); i++)
    {
        cout << "==" << moves[i].s.x << moves[i].s.y << moves[i].d.x << moves[i].d.y << moves[i].a.x << moves[i].a.y;
    }
    
    return 0;
}
