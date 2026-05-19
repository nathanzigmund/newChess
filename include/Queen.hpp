#ifndef QUEEN_HPP_
#define QUEEN_HPP_

#include "../include/Piece.hpp"

class Queen : public Piece {

    public:
        Queen(bool team);
        PieceType get_type() const override;

};

#endif