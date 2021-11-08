#include "ai.hpp"
#include "heuristics.cpp"

void alpha_beta_get_move(Board &board, Mode &mode){
    _Float32 best_score = numeric_limits<_Float32>::min(); 
    _Float32 worst_score = numeric_limits<_Float32>::max(); 
    _Float32 score = 0.0;

    short token = board.whites_turn ? 1 : 2;
    const bool calling_player = board.whites_turn;
    bool whites_turn = board.whites_turn; 

    vector<Move> moves = board.generate_moves(token);
    Move best_move = moves[0];
    u_short depth = moves.size() > 15 ? 1 : 5;


    iterv(moves){
        // move
        board.field(move_d(moves[i])) = token;
        board.field(move_s(moves[i])) = 0;
        board.field(move_a(moves[i])) = -1;

        score = alpha_beta(board, depth, best_score, worst_score, calling_player, not whites_turn, mode);

        // undo move
        board.field(move_a(moves[i])) = 0;
        board.field(move_d(moves[i])) = 0;
        board.field(move_s(moves[i])) = token;

        if (score > best_score){
            best_score = score;
            best_move = moves[i];
        }
    }

    board.field(move_d(best_move)) = token;
    board.field(move_s(best_move)) = 0;
    board.field(move_a(best_move)) = -1;

}

_Float32 alpha_beta(Board &board, u_short  &depth, _Float32 &a, _Float32 &b, const bool &calling_player, bool whites_turn, const Mode &mode){
    // Functionwide 
    short token = whites_turn?1:2;

    // Leaf-node Case
    if (depth==0 || board.has_lost(token)){
        
        short one = 1;
        short two = 2;
        _Float32 h_val_a, h_val_b;
        short enemy_token = (whites_turn)?2:1;
        
        switch (mode)
        {
        case a_b_mobility:
            h_val_a = mobility_evaluation(board, one);
            h_val_b = mobility_evaluation(board, two);
            if (calling_player) return (h_val_a-h_val_b);
            else
                return (h_val_b-h_val_a);
            break;

        case a_b_territorial:

            break;

        default:
            cout << "Err in leafnodecase\n";
            return 0.0f;
            break;
        }
    }

    // Non leaf-node Case
    _Float32 score = 0.0f;
    vector<Move> moves = board.generate_moves(token);

    iterv(moves){

        // move
        board.field(move_d(moves[i])) = token;
        board.field(move_s(moves[i])) = 0;
        board.field(move_a(moves[i])) = -1;

        score = alpha_beta(board, --depth, a, b, calling_player, not whites_turn,mode);

        // undo move
        board.field(move_a(moves[i])) = 0;
        board.field(move_d(moves[i])) = 0;
        board.field(move_s(moves[i])) = token;

        // maximizing 
        if (calling_player==whites_turn)a = max(a, score);
        // minimizing 
        else b = min(b, score);
        // cutoff
        if (b <= a) break;
        
    }

    return (calling_player==whites_turn)?a:b;
}