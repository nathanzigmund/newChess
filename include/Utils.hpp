#ifndef UTILS_HPP_
#define UTILS_HPP_
#include <iostream>
#include <vector>
#include "../include/all_headers.hpp"
namespace utils {
    std::string color_to_string(bool color);
    int char_to_int(char c);
    void display_pieces(Board b);
    std::vector<int> get_tile_key(int screen_size);
    bool in_bounds(int r, int c);
}   
#endif