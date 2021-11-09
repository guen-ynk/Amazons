#include "board.hpp"

using namespace std;
using namespace Eigen;

Board::Board(){
            whites_turn = true;
            board_size = 10;
            amazons_count = 4;
            field =  Matrix <short , 10, 10>::Zero();

            field(0,3) = 1;
            field(0,6) = 1;
            field(3,0) = 1;
            field(3,9) = 1;

            field(9,3) = 2;
            field(9,6) = 2;
            field(6,0) = 2;
            field(6,9) = 2;
        }
vector<Coordinates> Board::get_queen_positions(short &color){
            short counter = 0;
            vector<Coordinates> positions;
            for (size_t i = 0; i < board_size; i++)
            {
                for (size_t j = 0; j < board_size; j++)
                {
                    if(field(i,j)== color){
                        positions.push_back(Coordinates(i,j));
                        counter++;
                        if (counter == amazons_count)return positions;
                    }
                }
            }
            return positions;
            
        }
vector<Coordinates> Board::get_amazon_moves(Coordinates &c){
            short x = c.x;
            short y = c.y;                        
            vector<Coordinates> positions;
            // North
            int i = x-1;
            while(i>=0){ 
                if(field(i,y)==0)positions.push_back(Coordinates(i,y));
                else
                    break;
                i--;
            }

            // South
            i = x+1;
            for (; i < board_size; i++)
            {
                if(field(i,y)==0)positions.push_back(Coordinates(i,y));
                else
                    break;
            }
            
            // West
            i = y-1;
            while(i>=0){   
                if(field(x,i)==0)positions.push_back(Coordinates(x,i));
                else
                    break;
                i--;
            } 

            // East
            i = y+1;
            for (; i < board_size; i++)
            {
                if(field(x,i)==0)positions.push_back(Coordinates(x,i));
                else
                    break;
            }

            // SW
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x -= 1;
                y -= 1;
                if( x>=0 && y>=0 && field(x,y)==0)positions.push_back(Coordinates(x,y));
                else
                    break;
            }

            // NE
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x += 1;
                y += 1;
                if( x<board_size && y<board_size && field(x,y)==0)positions.push_back(Coordinates(x,y));
                else
                    break;
            }

            // SE
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x -= 1;
                y += 1;
                if( x>=0 && y<board_size && field(x,y)==0)positions.push_back(Coordinates(x,y));
                else
                    break;
            }

            // NW
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x += 1;
                y -= 1;
                if( x<board_size && y>=0 && field(x,y)==0)positions.push_back(Coordinates(x,y));
                else
                    break;
            }

            return positions;
        }
bool Board::has_lost(short &color){
            vector<Coordinates> queens = get_queen_positions(color);
            for (size_t i = 0; i < queens.size(); i++)
            {
                for (size_t j = 0; j < operations.size(); j++)
                {
                   queens[i].add(operations[j]);
                   if (0 <= queens[i].x && queens[i].x < board_size && 0 <= queens[i].y && queens[i].y < board_size){
                        if(field(queens[i].x,queens[i].y)==0) return false;
                   }
                   queens[i].sub(operations[j]);
                }
            }
            return true;
        }      
vector<Move> Board::generate_moves(short &color){

        vector<Move> moves;
        vector<Coordinates> queens = get_queen_positions(color);
        short sx,sy,dx,dy;
       
        for (size_t i = 0; i < queens.size(); i++)
        {
            vector<Coordinates> amazon_move = get_amazon_moves(queens[i]);
            for (size_t j = 0; j < amazon_move.size(); j++)
            {
                sx = amazon_move[j].x;
                sy = amazon_move[j].y;
                dx = sx;
                dy = sy;
                Coordinates d = Coordinates(dx,dy);

                // move
                field(move_ind(amazon_move[j])) = color;
                field(move_ind(queens[i])) = 0;

                // North
                for (size_t k = 1; k < board_size; k++)
                {
                    sx--;
                    if(sx>=0 && field(sx,sy)==0) moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else 
                        break;
                }
                sx = amazon_move[j].x;
                // South
                for (size_t k = 1; k < board_size; k++)
                {
                    sx++;
                    if(sx<board_size && field(sx,sy)==0) moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                sx = amazon_move[j].x;
                // West
                for (size_t k = 1; k < board_size; k++)
                {
                    sy--;
                    if(sy>=0 && field(sx,sy)==0)moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                sy = amazon_move[j].y;
                // East
                for (size_t k = 1; k < board_size; k++)
                {
                    sy++;
                    if(sy<board_size && field(sx,sy)==0)moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                sy = amazon_move[j].y;
                // Diagonals
                for (size_t k = 1; k < board_size; k++)
                {
                    sx--;
                    sy--;
                    if(sx>=0 && sy>=0 && field(sx,sy)==0)moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                sx = amazon_move[j].x;
                sy = amazon_move[j].y;

                for (size_t k = 1; k < board_size; k++)
                {
                    sx--;
                    sy++;
                    if(sx>=0 && sy<board_size && field(sx,sy)==0)moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                sx = amazon_move[j].x;
                sy = amazon_move[j].y;

                for (size_t k = 1; k < board_size; k++)
                {
                    sx++;
                    sy--;
                    if(sy>=0 && sx<board_size && field(sx,sy)==0)moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                sx = amazon_move[j].x;
                sy = amazon_move[j].y;

                for (size_t k = 1; k < board_size; k++)
                {
                    sx++;
                    sy++;
                    if(sx<board_size && sy<board_size && field(sx,sy)==0)moves.push_back(Move(queens[i],d,Coordinates(sx,sy)));
                    else
                        break;
                }
                // undo move
                field(move_ind(amazon_move[j])) = 0;
                field(move_ind(queens[i])) = color;
            }
            

        }
        
        return moves;
    }


void Board::debugout(){
    for (size_t i = 0; i < board_size; i++)
    {
        for (size_t j = 0; j < board_size; j++)
        {
            cout << field(i,j) << " ";
        }
        cout << "\n";
        
    }
    
    
}

/*
int main(int argc, char const *argv[])
{
    Board board1 = Board();
    
    cout << "field =" << endl << board1.field << endl;
    Coordinates temp(3,9);
    short test = 1;
    auto positions = board1.get_amazon_moves(temp);
    for (size_t i = 0; i < positions.size(); i++)
    {
        cout << positions[i].x << positions[i].y << endl;
    }
    cout << "field =" << endl << board1.field << endl;
 
    cout << "lost?" << board1.has_lost(test) << "\n";
    auto moves = board1.generate_moves(test);
    for (size_t i = 0; i < moves.size(); i++)
    {
        cout << "==" << moves[i].s.x << moves[i].s.y << moves[i].d.x << moves[i].d.y << moves[i].a.x << moves[i].a.y;
    }
    cout << "field =" << endl << board1.field << endl;

    return 0;
}
*/