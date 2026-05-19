
#ifndef PIECE_HPP_
#define PIECE_HPP_

#include <string>

// Enum to help your Move Validator identify the piece
enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King };

class Piece {
    protected:
    bool team;
    int piece_value;

    public: 
    Piece(bool team, int value);
    virtual ~Piece() {}

    virtual PieceType get_type() const = 0;

    int get_value();
    void print(); 
    bool get_team();
};

#endif