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

void init_formula(Board &board, formula &eval){
    eval.p = board.open_fields/board.board_size;
    eval.q = (1-eval.p);

    eval.w1 = 0.7f*eval.q;
    eval.w2 = 0.3f*eval.q;

    eval.w3 = 0.7f*eval.p;
    eval.w4 = 0.3f*eval.q;
}

void reset_matricies(Board &board){
    for (size_t i = 0; i < board.board_size; i++)
    {
        for (size_t j = 0; j < board.board_size; j++)
        {
            board.wq_h(i,j)=999;
            board.wk_h(i,j)=999;

            board.bq_h(i,j)=999;
            board.bk_h(i,j)=999;

        }
        
    }
    
}

void bfs(Board &board, Coordinates &pos, Matrix<short,Dynamic,Dynamic> &heuristic_board, bool mode){

vector<Coordinates> stack;
vector<Coordinates> level_two_stack; 
vector<Coordinates> level_three_stack;
stack.push_back(pos);
Coordinates iter=pos;
for (size_t k = 0; k < 100; k++)
{
    level_two_stack.clear();
    level_three_stack.clear();

    while (not stack.empty())
    {   
        iter = stack[0];
        // mode 1: queen; mode 0: kings
        level_two_stack = mode ? queen_moves(board, k,  heuristic_board, iter): king_moves(board, k,  heuristic_board, iter);
        if(not level_two_stack.empty())level_three_stack.insert(end(level_three_stack), begin(level_two_stack), end(level_two_stack));
        stack.erase(stack.begin());

    }
    if(not level_three_stack.empty())stack.insert(end(stack), begin(level_three_stack), end(level_three_stack));
    else break;
    }
}


vector<Coordinates> queen_moves(Board &board, size_t depth, Matrix<short,Dynamic,Dynamic> &heuristic_board,Coordinates &c){
            
            short x = c.x;
            short y = c.y;                        
            vector<Coordinates> positions;
            // North
            int i = x-1;
            while(i>=0){ 
                if(board.field(i,y)==0){
                    if(heuristic_board(i,y)>depth){
                        heuristic_board(i,y) = depth;
                        positions.push_back(Coordinates(i,y));
                    }
                }
                else
                    break;
                i--;
            }

            // South
            i = x+1;
            for (; i < board.board_size; i++)
            {
                if(board.field(i,y)==0){
                    if(heuristic_board(i,y)>depth){
                        heuristic_board(i,y) = depth;
                        positions.push_back(Coordinates(i,y));
                    }
                }
                else
                    break;
            }
            
            // West
            i = y-1;
            while(i>=0){   
                if(board.field(x,i)==0){
                    if(heuristic_board(x,i)>depth){
                        heuristic_board(x,i) = depth;
                        positions.push_back(Coordinates(x,i));
                    }
                }
                else
                    break;
                i--;
            } 

            // East
            i = y+1;
            for (; i < board.board_size; i++)
            {
                if(board.field(x,i)==0){
                     if(heuristic_board(x,i)>depth){
                        heuristic_board(x,i) = depth;
                        positions.push_back(Coordinates(x,i));
                    }
                }
                else
                    break;
            }

            // SW
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board.board_size; i++)
            {
                x -= 1;
                y -= 1;
                if( x>=0 && y>=0 && board.field(x,y)==0){
                     if(heuristic_board(x,y)>depth){
                        heuristic_board(x,y) = depth;
                        positions.push_back(Coordinates(x,y));
                    }
                } 
                else
                    break;
            }

            // NE
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board.board_size; i++)
            {
                x += 1;
                y += 1;
                if( x<board.board_size && y<board.board_size && board.field(x,y)==0){
                     if(heuristic_board(x,y)>depth){
                        heuristic_board(x,y) = depth;
                        positions.push_back(Coordinates(x,y));
                    }
                }
                else
                    break;
            }

            // SE
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board.board_size; i++)
            {
                x -= 1;
                y += 1;
                if( x>=0 && y<board.board_size && board.field(x,y)==0){
                     if(heuristic_board(x,y)>depth){
                        heuristic_board(x,y) = depth;
                        positions.push_back(Coordinates(x,y));
                    }
                }
                else
                    break;
            }

            // NW
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board.board_size; i++)
            {
                x += 1;
                y -= 1;
                if( x<board.board_size && y>=0 && board.field(x,y)==0){
                     if(heuristic_board(x,y)>depth){
                        heuristic_board(x,y) = depth;
                        positions.push_back(Coordinates(x,y));
                    }
                }
                else
                    break;
            }
            return positions;
        }

vector<Coordinates> king_moves(Board &board, size_t depth, Matrix<short,Dynamic,Dynamic> &heuristic_board,Coordinates &c){
            
            short x = c.x;
            short y = c.y;                        
            vector<Coordinates> positions;
            // North
            int i = x-1;
            if(i>=0){ 
                if(board.field(i,y)==0){
                    if(heuristic_board(i,y)>depth){
                        heuristic_board(i,y) = depth;
                        positions.push_back(Coordinates(i,y));
                    }
                }
            }

            // South
            i = x+1;
            if(i<board.board_size)
            {
                if(board.field(i,y)==0){
                    if(heuristic_board(i,y)>depth){
                        heuristic_board(i,y) = depth;
                        positions.push_back(Coordinates(i,y));
                    }
                }
            }
            
            // West
            i = y-1;
            if(i>=0){   
                if(board.field(x,i)==0){
                    if(heuristic_board(x,i)>depth){
                        heuristic_board(x,i) = depth;
                        positions.push_back(Coordinates(x,i));
                    }
                }
            } 

            // East
            i = y+1;
            if(i < board.board_size)
            {
                if(board.field(x,i)==0){
                     if(heuristic_board(x,i)>depth){
                        heuristic_board(x,i) = depth;
                        positions.push_back(Coordinates(x,i));
                    }
                }
            }

            // SW
            x = c.x-1;
            y = c.y-1; 
            i = 0;
           
            if( x>=0 && y>=0 && board.field(x,y)==0){
                    if(heuristic_board(x,y)>depth){
                    heuristic_board(x,y) = depth;
                    positions.push_back(Coordinates(x,y));
                }
            } 
          

            // NE
            x = c.x+1;
            y = c.y+1; 

            if( x<board.board_size && y<board.board_size && board.field(x,y)==0){
                    if(heuristic_board(x,y)>depth){
                    heuristic_board(x,y) = depth;
                    positions.push_back(Coordinates(x,y));
                }
            }
            

            // SE
            x = c.x-1;
            y = c.y+1; 
   
            if( x>=0 && y<board.board_size && board.field(x,y)==0){
                    if(heuristic_board(x,y)>depth){
                    heuristic_board(x,y) = depth;
                    positions.push_back(Coordinates(x,y));
                }
            }
          
            // NW
            x = c.x+1;
            y = c.y-1; 
          
            if( x<board.board_size && y>=0 && board.field(x,y)==0){
                    if(heuristic_board(x,y)>depth){
                    heuristic_board(x,y) = depth;
                    positions.push_back(Coordinates(x,y));
                }
            }
              
            return positions;
        }

void calculate_t_p_heuristic(Board &board, short &token, formula &eval){

    for (size_t i = 0; i < board.board_size; i++)
    {
        for (size_t j = 0; j < board.board_size; j++)
        {
            if(board.field(i,j)!=0)continue;

            if(token == 1){

                if(board.wq_h(i,j)==board.bq_h(i,j)){
                    if (board.wq_h(i,j)!=999) eval.t1 += 0.2f;
                }else eval.t1 +=  board.wq_h(i,j)<board.bq_h(i,j)?1.0f:-1.0f;

                if(board.wk_h(i,j)==board.bk_h(i,j)){
                    if (board.wk_h(i,j)!=999) eval.t2 += 0.2f;
                }else eval.t2 +=  board.wk_h(i,j)<board.bk_h(i,j)?1.0f:-1.0f;
                
                eval.c1 += (pow(2.0f,-board.wq_h(i,j)))-(pow(2.0f,-board.bq_h(i,j)));
                eval.c2 += min(1.0f,max(-1.0f, (board.bk_h(i,j)-board.wk_h(i,j))/6.0f));
            
            }else{

                if(board.wq_h(i,j)==board.bq_h(i,j)){
                    if (board.bq_h(i,j)!=999) eval.t1 += 0.2f;
                }else eval.t1 +=  board.bq_h(i,j)<board.wq_h(i,j)?1.0f:-1.0f;

                if(board.wk_h(i,j)==board.bk_h(i,j)){
                    if (board.bk_h(i,j)!=999) eval.t2 += 0.2f;
                }else eval.t2 +=  board.bk_h(i,j)<board.wk_h(i,j)?1.0f:-1.0f;
                
                eval.c1 += (pow(2.0f,-board.bq_h(i,j)))-(pow(2.0f,-board.wq_h(i,j)));
                eval.c2 += min(1.0f,max(-1.0f, (board.wk_h(i,j)-board.bk_h(i,j))/6.0f));
            
            }

        }
        
    }
    



}

_Float32 territorial_positional_evaluation(Board &board, short &token){
    formula eval;
    init_formula(board, eval);
    reset_matricies(board);
    short one = 1;
    short two = 2;

    vector<Coordinates> white_amazons = board.get_queen_positions(one);
    vector<Coordinates> black_amazons = board.get_queen_positions(two);

    for (size_t i = 0; i < board.amazons_count; i++)
    {
        bfs(board, white_amazons[i], board.wq_h, true);
        bfs(board, white_amazons[i], board.wk_h, false);

        bfs(board, black_amazons[i], board.bq_h, true);
        bfs(board, black_amazons[i], board.bk_h, false);

    }
    
    calculate_t_p_heuristic(board, token, eval);
    return (eval.w1*eval.t1)+(eval.w2*eval.c1*2)+(eval.w3*eval.t2)+(eval.w4*eval.c2);

}