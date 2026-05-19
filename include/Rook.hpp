#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "../include/Piece.hpp"


class Rook : public Piece {
    private:
    bool has_moved;
    public:
        Rook(bool team, bool has_moved);
        PieceType get_type() const override;
        void move();
        bool hasMoved();
};

#endif