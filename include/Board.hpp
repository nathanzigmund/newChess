#ifndef BOARD_HPP_
#define BOARD_HPP_
#include <iostream>
#include <vector>
#include "../include/Square.hpp"
struct Move {
        int to_row;
        int to_col;

        Move(int r, int c) : to_row(r), to_col(c) {}

        bool operator==(const Move& other) const {
            return to_row == other.to_row && to_col == other.to_col;
        }
    };

class Board {
    
    private:
    bool perspective;
    Square board[8][8];
    void init_pieces(bool team);
    void get_rook_moves(int row, int col, Piece* p, std::vector<Move>& moves);
    void get_bishop_moves(int row, int col, Piece* p, std::vector<Move>& moves);
    void get_king_moves(int row, int col, Piece* p, std::vector<Move>& moves);
    void get_pawn_moves(int row, int col, Piece* p, std::vector<Move>& moves);
    void get_knight_moves(int row, int col, Piece* p, std::vector<Move>& moves);
    void get_queen_moves(int row, int col, Piece* p, std::vector<Move>& moves);


    public:
    Board(bool perspective);
    bool get_perspective();
    void display_board();
    Square get_square(int row, int col);
    void move_piece(int old_row, int old_col, int new_row, int new_col);
    std::vector<Move> get_moves_for_piece(int row, int col);
    

    

};

#endif
