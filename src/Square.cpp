#include "../include/Square.hpp"
#include "../include/Utils.hpp"

#include <iostream>
Square::Square(bool color, Piece* piece){
    this->color = color;
    this-> piece = piece;
}

void Square::add_piece(Piece* piece) {
    this->piece = piece;
}
void Square:: remove_piece() {
    this->piece = nullptr;
}
Piece* Square::get_piece() {
     return this->piece;
}
void Square::print(){
 std::cout<< "Color: " << utils::color_to_string(color) << " piece: " << std::endl;
 if(piece) piece->print();
 else std::cout << "none" <<std::endl;
}
void Square::set_color(bool color) {
    this->color = color;
}
bool Square::get_color() {
    return color;
}