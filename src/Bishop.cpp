#include "../include/Bishop.hpp"

Bishop::Bishop(bool team) : Piece(team, 3) {}

PieceType Bishop::get_type() const {
    return PieceType::Bishop;
}

