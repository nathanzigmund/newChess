#include "../include/Board.hpp"
#include "../include/all_headers.hpp"
#include <iostream>
#include <vector>
#include "../include/Utils.hpp"
Board::Board() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            bool square_color = ((i+j) % 2 == 0) ? true : false;
            board[i][j] = Square (square_color, nullptr);
        }
    }
    init_pieces();
}
void Board::init_pieces() {
    //WHITE PAWNS
    for(int i = 0;i < 8;i++) {
        board[1][i].add_piece(new Pawn(true, false));
    }
    //WHITE ROOKS
    board[0][0].add_piece(new Rook(true, false));
    board[0][7].add_piece(new Rook(true, false));
    //WHITE KNIGHTS
    board[0][1].add_piece(new Knight(true));
    board[0][6].add_piece(new Knight(true));

    //WHITE BISH
    board[0][2].add_piece(new Bishop(true));
    board[0][5].add_piece(new Bishop(true));

    board[0][4].add_piece(new King(true, false, false));
    board[0][3].add_piece(new Queen(true));

    //BLACK PAWNS
    for(int i = 0;i < 8;i++) {
        board[6][i].add_piece(new Pawn(false,false));
    }
    //BLACK ROOKS
    board[7][0].add_piece(new Rook(false, false));
    board[7][7].add_piece(new Rook(false, false));
    //BLACK KNIGHTS
    board[7][1].add_piece(new Knight(false));
    board[7][6].add_piece(new Knight(false));

    //BLACK BISH
    board[7][2].add_piece(new Bishop(false));
    board[7][5].add_piece(new Bishop(false));

    board[7][3].add_piece(new Queen(false));
    board[7][4].add_piece(new King(false,false, false));

}

/*

display_board():
const int screen size_

void Board::display_board() {
    for(int i = 7; i >= 0; i--) {
        for(int j = 7; j>= 0;j--) {
            if(board[i][j].get_color()) std::cout << " W ";
            else std::cout << " B ";
        }
        std::cout << "\n";
    }
}


*/
//
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
    for(int xscreen = SCREEN_SIZE - 1; xscreen >= 0; xscreen--) {
        for(int yscreen = SCREEN_SIZE - 1; yscreen >= 0; yscreen--) {
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
        std::cout << "found piece, moving it now " << std::endl;
        piece->print();
    }
    else std::cout << "what piece!! " << std::endl;
    board[new_row][new_col].add_piece(piece);
    old_square.remove_piece();

}

Square Board::get_square(int row, int col) {
    return board[row][col];
}