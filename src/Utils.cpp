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
    for(int col = 7; col >= 0; col--) {
        for(int row = 7; row>= 0;row--) {
            Piece* p = b.get_square(col,row).get_piece();
            
            if(p) {
                std::cout << " " << utils::color_to_string(p->get_team()) << " ";
            }
            else std::cout << "   ";
            
        }
        std::cout << "\n";
    }
}

/**
 * @brief helper function for the board::display_board() comand
 * @param screen_size size of screen;
 * @return list of tiles that are holding pieces aka: actual piece
 */
std::vector<int> utils::get_tile_key(int screen_size) {
    std::vector<int> nums;
    for(int i = 0; i < screen_size; i++) {
        if(i % 3 == 1) nums.push_back(i);
    }
    return nums;
}

bool utils::in_bounds(int r, int c) {
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}
