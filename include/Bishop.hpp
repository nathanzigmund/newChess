#ifndef BISHOP_HPP_
#define BISHOP_HPP_

#include "../include/Piece.hpp"

class Bishop : public Piece {

    public:
        Bishop(bool team);
        PieceType get_type() const override;

};

#endif