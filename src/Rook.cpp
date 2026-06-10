#include "../include/Rook.hpp"
#include "../include/Utils.hpp"

Rook::Rook(bool team, bool has_moved) : Piece(team, 5), has_moved(has_moved) {

}
PieceType Rook::get_type() const {
    return PieceType::Rook;
}
bool Rook::hasMoved() {
    return has_moved;
}

void Rook::move() {
    has_moved = true;
}
