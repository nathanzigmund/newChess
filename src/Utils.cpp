#include "../include/Utils.hpp"
#include <iostream>
int utils::char_to_int(char c) {
    if( c >= 'a' && c <= 'h') return c - 'a';
    if (c >= '1' && c <= '8') return c - '1';
    throw std::invalid_argument("invalid coordinate");
}

std::string utils::color_to_string(bool color) {
    if(color) return "white";
    else return "black";
}

void utils::display_pieces(Board b) {
    for(int i = 7; i >= 0; i--) {
        for(int j = 7; j>= 0;j--) {
            Piece* p = b.get_square(i,j).get_piece();
            
            if(p) {
                std::cout << " " << p->get_value() << " ";
            }
            else std::cout << "   ";
            
        }
        std::cout << "\n";
    }
}

std::vector<int> utils::get_tile_key(int screen_size) {
    std::vector<int> nums;
    for(int i = 0; i < screen_size; i++) {
        if(i % 3 == 1) nums.push_back(i);
    }
    return nums;
}