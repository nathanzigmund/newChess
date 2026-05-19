#ifndef SQUARE_HPP_
#define SQUARE_HPP_
#include "../include/Piece.hpp"
class Square {
private:
    bool color;
    Piece* piece;

public:
    Square() : color(true), piece(nullptr) {}
    Square(bool color, Piece* piece);
    bool is_empty();
    void add_piece(Piece* piece);
    void remove_piece();
    Piece* get_piece();
    void print();
    void set_color(bool color);
    bool get_color();

};

#endif