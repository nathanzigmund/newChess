#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include "../include/Piece.hpp"

class Knight : public Piece {

    public:
        Knight(bool team);
        PieceType get_type() const override;
};

#endif