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

     

    // Liste:
    // (0,4),(0,6),(3,0),(3,9)



    return 0;
}
