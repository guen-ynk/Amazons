#include "heuristics.hpp"

_Float32 mobility_evaluation(Board &board, short &token){
    _Float32 score = 0.0;
    vector<Coordinates> amazons_pos = board.get_queen_positions(token);
    short x,y;

    iterv(amazons_pos){
        vector<Coordinates> moves = board.get_amazon_moves(amazons_pos[i]);
        iterv_inner(moves){
          
            x = moves[j].x;
            y = moves[j].y; 

            // move
            board.field(move_ind(moves[j])) = token;
            board.field(move_ind(amazons_pos[i])) = 0;

            // North
            for (size_t k = 1; k < board.board_size; k++)
            {
                x--;
                if(x >=0 && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            x = moves[j].x;
            // South
            for (size_t k = 1; k < board.board_size; k++)
            {
                x++;
                if(x < board.board_size && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            x = moves[j].x;
            // West
            for (size_t k = 1; k < board.board_size; k++)
            {
                y--;
                if(y >= 0 && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            y = moves[j].y;        
            // East
            for (size_t k = 1; k < board.board_size; k++)
            {
                y++;
                if(y < board.board_size && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            y = moves[j].y;        
            // Diagonals
            for (size_t k = 1; k < board.board_size; k++)
            {
                x--;
                y--;
                if(x >=0 && y>=0 && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            x = moves[j].x;
            y = moves[j].y; 
            for (size_t k = 1; k < board.board_size; k++)
            {
                x--;
                y++;
                if(x >=0 && y < board.board_size && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            x = moves[j].x;
            y = moves[j].y; 
            for (size_t k = 1; k < board.board_size; k++)
            {
                x++;
                y--;
                if(x < board.board_size && y>=0 && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
            x = moves[j].x;
            y = moves[j].y; 
            for (size_t k = 1; k < board.board_size; k++)
            {
                x++;
                y++;
                if(x < board.board_size && y < board.board_size && board.field(x,y)==0)score+=1.0f;
                else
                    break;
            }
          
            // undo move
            board.field(move_ind(amazons_pos[i])) = token;
            board.field(move_ind(moves[j])) = 0;
        }
    }
    return score;
}
    
