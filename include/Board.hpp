#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "../include/Square.hpp"
class Board {
    private:
    Square board[8][8];
    void init_pieces();

    public:
    Board();
    void display_board();
    Square get_square(int row, int col);
    void move_piece(int old_row, int old_col, int new_row, int new_col);

    

};

#endif
