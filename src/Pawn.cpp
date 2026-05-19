#include "../include/Pawn.hpp"
#include "../include/Utils.hpp"
#include <iostream>
Pawn::Pawn(bool team, bool has_moved) : Piece(team,1), has_moved(has_moved) {

}

PieceType Pawn::get_type() const {
    return PieceType::Pawn;
}

bool Pawn::hasMoved() {
    return has_moved;
}

void Pawn::move() {
    has_moved = false;
}
