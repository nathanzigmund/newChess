#include "../include/Piece.hpp"
#include "../include/Utils.hpp"
#include <iostream>
Piece::Piece(bool team, int value) {
    this->team = team;
    this->piece_value = value;
}

void Piece::print(){
     
    std::cout << "Team: " << utils::color_to_string(team) << " value: " << piece_value <<std::endl; 
}

int Piece::get_value(){
    return piece_value;
}

bool Piece::get_team() {
    return team;
}
