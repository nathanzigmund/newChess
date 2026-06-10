#include "../include/Board.hpp"
#include "../include/all_headers.hpp"
#include <iostream>
#include <vector>
#include "../include/Utils.hpp"
Board::Board(bool perspective) {
    this->perspective = perspective;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            bool square_color = ((i+j) % 2 == 0) ? true : false;
            board[i][j] = Square (square_color, nullptr);
        }
    }
    init_pieces(perspective);
}
void Board::init_pieces(bool team) {
    //WHITE PAWNS
    for(int i = 0;i < 8;i++) {
        board[1][i].add_piece(new Pawn(!team, false));
    }
    //WHITE ROOKS
    board[0][0].add_piece(new Rook(!team, false));
    board[0][7].add_piece(new Rook(!team, false));
    //WHITE KNIGHTS
    board[0][1].add_piece(new Knight(!team));
    board[0][6].add_piece(new Knight(!team));

    //WHITE BISH
    board[0][2].add_piece(new Bishop(!team));
    board[0][5].add_piece(new Bishop(!team));

    board[0][4].add_piece(new King(!team, false, false));
    board[0][3].add_piece(new Queen(!team));

    //BLACK PAWNS
    for(int i = 0;i < 8;i++) {
        board[6][i].add_piece(new Pawn(team,false));
    }
    //BLACK ROOKS
    board[7][0].add_piece(new Rook(team, false));
    board[7][7].add_piece(new Rook(team, false));
    //BLACK KNIGHTS
    board[7][1].add_piece(new Knight(team));
    board[7][6].add_piece(new Knight(team));

    //BLACK BISH
    board[7][2].add_piece(new Bishop(team));
    board[7][5].add_piece(new Bishop(team));

    board[7][3].add_piece(new Queen(team));
    board[7][4].add_piece(new King(team,false, false));

}


std::string curr_color_string(bool c) {
    if(c) {
        return "█";
    } 
    else return " ";
}

void Board::display_board() {
    const int TILE_SIZE = 3;
    const int SCREEN_SIZE = 8 * TILE_SIZE;
    std::vector<int> chessboard_tiles = utils::get_tile_key(SCREEN_SIZE);
    //std::string whiteSquare = "███"; 
    //std::string blackSquare = "   ";
    for(int xscreen = 0; xscreen < SCREEN_SIZE; xscreen++) {
        for(int yscreen = 0; yscreen < SCREEN_SIZE; yscreen++) {
            int curr_row = xscreen / 3;
            int curr_col = yscreen / 3;
            bool current_square_color = board[curr_row][curr_col].get_color();
            if( xscreen % 3 == 1 && yscreen % 3 == 1) {
                //chessboard tile
                Piece* p = board[curr_row][curr_col].get_piece();
                if(p) {
                    std::cout << p->get_value();
                } else std::cout << curr_color_string(current_square_color);
            } else {
                std::cout << curr_color_string(current_square_color);
            }
        }
        std::cout << std::endl;
    }
}

void Board::move_piece(int old_row, int old_col, int new_row, int new_col) {
    Square& old_square = board[old_row][old_col];
    Piece* piece = old_square.get_piece();
    if(piece) {
        piece->print();
         
        if(piece->get_type()== PieceType::King ||piece->get_type()== PieceType::Pawn || piece->get_type()== PieceType::Rook ) {
            piece->move();
        }
        board[new_row][new_col].add_piece(piece);
        old_square.remove_piece();
    if(old_square.is_empty()) std::cout << "Piece moved!" << std::endl;
    }
    else std::cout << "what piece!! " << std::endl;
   

}

Square Board::get_square(int row, int col) {
    return board[row][col];
}
bool Board::get_perspective() {
    return perspective;
}

std::vector<Move> Board::get_moves_for_piece(int row, int col) {
    std::vector<Move> moves;
    Piece* p = board[row][col].get_piece();

    if(!p) return moves;

    switch(p->get_type()) {
        case PieceType::Rook:
            get_rook_moves(row, col,p,moves);
            break;
        case PieceType::Bishop:
            get_bishop_moves(row,col, p, moves);
            break;
        case PieceType::Knight:
            get_knight_moves(row, col,p,moves);
            break;
        case PieceType::King:
            get_king_moves(row,col, p, moves);
            break;
        case PieceType::Queen:
            get_queen_moves(row,col, p, moves);
            
            break;
        case PieceType::Pawn:
            get_pawn_moves(row,col,p,moves);
            break;
    }
        
    return moves;
}
void Board::get_rook_moves(int row, int col, Piece* p, std::vector<Move>& moves) {
    bool team = p->get_team();
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0, 1} };
    
    for (auto& dir : directions) {
        int r = row + dir[0];
        int c = col + dir[1];

        while (utils::in_bounds(r,c)) {
            if (board[r][c].is_empty()) {
                moves.push_back({r, c});
            } else {
                // Enemy piece = capture and stop
                if (board[r][c].get_piece()->get_team() != team) {
                    moves.push_back({r, c});
                } 
                
                break; // Hit a piece, stop sliding in this direction
            }
            r += dir[0];
            c += dir[1];
        }
    }
}
void Board::get_bishop_moves(int row, int col, Piece* p, std::vector<Move>& moves) {
    bool team = p->get_team();
    int directions[4][2] = {{-1,-1}, {1,1}, {1,-1}, {-1, 1} };
    
    for (auto& dir : directions) {
        int r = row + dir[0];
        int c = col + dir[1];

        while (utils::in_bounds(r,c)) {
            if (board[r][c].is_empty()) {
                moves.push_back({r, c});
            } else {
                // Enemy piece = capture and stop
                if (board[r][c].get_piece()->get_team() != team) {
                    moves.push_back({r, c});
                }
                break; // Hit a piece, stop sliding in this direction
            }
            r += dir[0];
            c += dir[1];
        }
    }
}

void Board::get_pawn_moves(int row, int col, Piece* p, std::vector<Move>& moves) {
    bool team = p->get_team();
    int direction;
    
    //if white and perspective white, move up board (negative)
    // if black and black perspective, move down board (positive)

    if((team && perspective )|| (!team && !perspective) ) direction = -1;
    else direction = 1;

    
    bool has_moved = dynamic_cast<Pawn*>(p)->hasMoved();
    if(!has_moved) {
        moves.push_back({row + (2 * direction),col});
    }
    int r = row + direction;
    if(utils::in_bounds(r,col))
    moves.push_back({r,col});
    int left_c = col - 1;
    int right_c = col + 1;
    //capture logic
    if(left_c >= 0) {
        Piece* lp = board[r][left_c].get_piece();
        if(lp) {
            if(lp->get_team() != team) moves.push_back({r,left_c});
        }
        
    }
    if(right_c < 8) {
        Piece* rp = board[r][right_c].get_piece();
        if(rp) {
            if(rp->get_team() != team) moves.push_back({r,right_c});
        }
        
    }
}

void Board::get_king_moves(int row, int col, Piece* p, std::vector<Move>& moves) {
    bool team = p->get_team();
    int directions[8][2] = {{-1,-1}, {1,1}, {1,-1}, {-1, 1}, {-1,0}, {1,0}, {0,-1}, {0, 1} };
    
    for(auto& dir : directions) {
        int r = row + dir[0];
        int c = col + dir[1];
        
        if(utils::in_bounds(r,c)) {
            if (board[r][c].is_empty()) {
                moves.push_back({r, c});
            } else {
                // Enemy piece = capture and stop
                if (board[r][c].get_piece()->get_team() != team) {
                    moves.push_back({r, c});
                }
            }
        }
       
    }
     //castling
    if(dynamic_cast<King*>(p)->hasMoved() == false) {
         Piece* queen_rook = board[row][0].get_piece();
         Piece* king_rook = board[row][7].get_piece();
         if(queen_rook && queen_rook->get_type() == PieceType::Rook) {
            if(dynamic_cast<Rook*>(queen_rook)->hasMoved() == false) {
                bool empty = true;
                for(int i = 1; i < col; i++ ) {
                    if(board[row][i].is_empty() == false) empty = false; 
                }
                if(empty) moves.push_back({row,0});
            }
         }
         if(king_rook && king_rook->get_type() == PieceType::Rook) {
            if(dynamic_cast<Rook*>(king_rook)->hasMoved() == false) {
                bool empty = true;
                for(int i = col + 1; i < 7; i++ ) {
                    if(board[row][i].is_empty() == false) empty = false; 
                }
                if(empty) moves.push_back({row,7});
            }
         }
    }
   
}


void Board::get_knight_moves(int row, int col, Piece* p, std::vector<Move>& moves) {
    bool team = p->get_team();
    int directions[8][2] = {{-1,-2}, {-1,2}, {1,-2}, {1, 2}, {-2,1}, {-2,-1}, {2, 1}, {2, -1} };
    
    for(auto& dir : directions) {
        int r = row + dir[0];
        int c = col + dir[1];

        if(utils::in_bounds(r,c)) {
            if (board[r][c].is_empty()) {
                moves.push_back({r, c});
            } else {
                // Enemy piece = capture and stop
                if (board[r][c].get_piece()->get_team() != team) {
                    moves.push_back({r, c});
                }
            }
        }
    }
}

void Board::get_queen_moves(int row, int col, Piece* p, std::vector<Move>& moves) {
    bool team = p->get_team();
    int directions[8][2] = {{-1,-1}, {1,1}, {1,-1}, {-1, 1}, {-1,0}, {1,0}, {0,-1}, {0, 1} };
    
    for(auto& dir : directions) {
        int r = row + dir[0];
        int c = col + dir[1];
        
        while (utils::in_bounds(r,c)) {
            if (board[r][c].is_empty()) {
                moves.push_back({r, c});
            } else {
                // Enemy piece = capture and stop
                if (board[r][c].get_piece()->get_team() != team) {
                    moves.push_back({r, c});
                }
                break; // Hit a piece, stop sliding in this direction
            }
            r += dir[0];
            c += dir[1];
        }
    
    }
}