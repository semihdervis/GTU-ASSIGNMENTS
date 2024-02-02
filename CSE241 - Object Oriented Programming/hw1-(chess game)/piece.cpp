#include <iostream>
#include "piece.h"

using namespace std;

char Piece::getSymbol() const {
    switch (type) {
    case KING:   return (color == WHITE) ? 'K' : 'k';
    case QUEEN:  return (color == WHITE) ? 'Q' : 'q';
    case BISHOP: return (color == WHITE) ? 'B' : 'b';
    case KNIGHT: return (color == WHITE) ? 'H' : 'h';
    case ROOK:   return (color == WHITE) ? 'R' : 'r';
    case PAWN:   return (color == WHITE) ? 'P' : 'p';
    case EMPTY:  return '.';
    default:     return 'X'; // Assuming 'X' as the default character for unknown pieces
    }
}

PieceType Piece::getTypeFromSymbol(char symbol) {
    switch (symbol) {
        case 'K': return KING;
        case 'k': return KING;
        case 'Q': return QUEEN;
        case 'q': return QUEEN;
        case 'B': return BISHOP;
        case 'b': return BISHOP;
        case 'H': return KNIGHT;
        case 'h': return KNIGHT;
        case 'R': return ROOK;
        case 'r': return ROOK;
        case 'P': return PAWN;
        case 'p': return PAWN;
        case '.': return EMPTY;
        default: return EMPTY;
    }
}

PieceColor Piece::getColorFromSymbol(char symbol) {
    switch (symbol) {
        case 'K':
        case 'Q':
        case 'B':
        case 'H':
        case 'R':
        case 'P':
            return WHITE;
        case 'k':
        case 'q':
        case 'b':
        case 'h':
        case 'r':
        case 'p':
            return BLACK;
        case '.':
            return NONE;
        default: return NONE;
    }
}
