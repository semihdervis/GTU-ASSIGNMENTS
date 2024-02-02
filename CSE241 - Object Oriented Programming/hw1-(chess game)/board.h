#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "piece.h"

using namespace std;

class Board {
public:
    Board();
    void print() const;
    bool move();
    bool isValid(const Piece& src, const Piece& dst) const;
    bool isValidKing(const Piece& src, const Piece& dst) const;
    bool isValidQueen(const Piece& src, const Piece& dst) const;
    bool isValidBishop(const Piece& src, const Piece& dst) const;
    bool isValidKnight(const Piece& src, const Piece& dst) const;
    bool isValidRook(const Piece& src, const Piece& dst) const;
    bool isValidPawn(const Piece& src, const Piece& dst) const;
    bool isEnemy(const Piece& src, const Piece& dst) const;
    void suggest();
    double score() const;
    bool isUnderAttack(const Piece& dst) const;
    bool save() const;
    bool load();
private:
    std::vector<std::vector<Piece> > board;
	PieceColor turn;
};

#endif // BOARD_H