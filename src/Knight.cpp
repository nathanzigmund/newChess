#include "../include/Knight.hpp"

Knight::Knight(bool team) : Piece(team, 3) {}

PieceType Knight::get_type() const {
    return PieceType::Knight;
}

