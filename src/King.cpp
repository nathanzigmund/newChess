#include "../include/King.hpp"
#include "../include/Utils.hpp"
#include <iostream>
King::King(bool team, bool has_moved, bool in_check) : Piece(team,100), has_moved(has_moved), in_check(in_check) {
}

PieceType King::get_type() const {
    return PieceType::King;
}

bool King::hasMoved() {
    return has_moved;
}
bool King::isChecked() {
    return in_check;
}
void King::move() {
    has_moved = true;
}

void King::setCheck(bool b) {
    in_check = b;
}