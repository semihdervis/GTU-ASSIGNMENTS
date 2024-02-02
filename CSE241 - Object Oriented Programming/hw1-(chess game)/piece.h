#ifndef PIECE_H
#define PIECE_H

#include <iostream>

using namespace std;

enum PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum PieceColor { WHITE, BLACK, NONE };

class Piece {
public:
    Piece(PieceType t, PieceColor c) : type(t), color(c) {}
    Piece() : type(PieceType::EMPTY), color(PieceColor::NONE) {}
    friend class Board;
    char getSymbol() const;
    static PieceType getTypeFromSymbol(char symbol);
    static PieceColor getColorFromSymbol(char symbol);

private:
    int x, y;
    PieceType type;
    PieceColor color;
};

#endif // PIECE_H