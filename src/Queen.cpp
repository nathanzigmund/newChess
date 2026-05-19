#include "../include/Queen.hpp"

Queen::Queen(bool team) : Piece(team, 9) {}

PieceType Queen::get_type() const {
    return PieceType::Queen;
}

