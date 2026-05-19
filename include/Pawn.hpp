#ifndef PAWN_HPP_
#define PAWN_HPP_

#include "../include/Piece.hpp"

class Pawn : public Piece {
    private:
        bool has_moved;

    public:
        Pawn(bool team, bool has_moved);
        bool hasMoved();
        PieceType get_type() const override;
        void move();

};

#endif