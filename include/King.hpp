#ifndef KING_HPP_
#define KING_HPP_

#include "../include/Piece.hpp"

class King : public Piece {
    private:
        bool has_moved;
        bool in_check;

    public:
        King(bool team, bool has_moved, bool in_check);
        bool hasMoved();
        bool isChecked();
        PieceType get_type() const override;
        void move();
        void setCheck(bool b);

};



#endif