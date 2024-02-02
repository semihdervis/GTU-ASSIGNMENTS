#include <iostream>
#include "board.h"
#include "piece.h"
#include <iostream>
#include <fstream>

using namespace std;

Board::Board() {
    board.resize(8, std::vector<Piece>(8, Piece()));
    
    // Set up black pieces
    board[0][0] = Piece(PieceType::ROOK, PieceColor::BLACK);
    board[0][1] = Piece(PieceType::KNIGHT, PieceColor::BLACK);
    board[0][2] = Piece(PieceType::BISHOP, PieceColor::BLACK);
    board[0][3] = Piece(PieceType::QUEEN, PieceColor::BLACK);
    board[0][4] = Piece(PieceType::KING, PieceColor::BLACK);
    board[0][5] = Piece(PieceType::BISHOP, PieceColor::BLACK);
    board[0][6] = Piece(PieceType::KNIGHT, PieceColor::BLACK);
    board[0][7] = Piece(PieceType::ROOK, PieceColor::BLACK);

    for (int i = 0; i < 8; ++i) {
        board[1][i] = Piece(PieceType::PAWN, PieceColor::BLACK);
    }

    // Set up white pieces
    board[7][0] = Piece(PieceType::ROOK, PieceColor::WHITE);
    board[7][1] = Piece(PieceType::KNIGHT, PieceColor::WHITE);
    board[7][2] = Piece(PieceType::BISHOP, PieceColor::WHITE);
    board[7][3] = Piece(PieceType::QUEEN, PieceColor::WHITE);
    board[7][4] = Piece(PieceType::KING, PieceColor::WHITE);
    board[7][5] = Piece(PieceType::BISHOP, PieceColor::WHITE);
    board[7][6] = Piece(PieceType::KNIGHT, PieceColor::WHITE);
    board[7][7] = Piece(PieceType::ROOK, PieceColor::WHITE);

    for (int i = 0; i < 8; ++i) {
        board[6][i] = Piece(PieceType::PAWN, PieceColor::WHITE);
    }

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].x = i;
			board[i][j].y = j;
		}
	}

    turn = WHITE;
}

void Board::print() const {
    for (int i = 0; i < 8; i++) {
        cout << 8 - i << " | ";
        for (int j = 0; j < 8; j++) {
            cout << board[i][j].getSymbol() << " ";
        }
        cout << endl;
    }
    cout << "    ";
    for (int i = 0; i < 16; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "    ";
    for (char c : "abcdefgh") {
        cout << c << " ";
    }
    cout << endl << endl;
}

bool Board::isEnemy(const Piece& src, const Piece& dst) const {
	if (src.color == WHITE && dst.color == BLACK) return true;
	if (src.color == BLACK && dst.color == WHITE) return true;
	return false;
}


bool Board::move() {
	string str;
	(turn == WHITE) ? cout << "[White's turn]" << endl : cout << "[Black's turn]" << endl;
	cout << "Enter your move: ";
	cin >> str;
	if (str == "suggest") {
		suggest();
		return false;
	}
	if (str == "save") {
		save();
		return false;
	}
	int y1 = str[0] - 'a';
	int x1 = '8' - str[1];
	int y2 = str[2] - 'a';
	int x2 = '8' - str[3];
	if (x1<0 || x1>7 || y1<0 || y1>7 || x2<0 || x2>7 || y2<0 || y2>7) {
		std::cout << "Invalid move: out of bounds" << std::endl;
		return false;
	}
	Piece& src = board[x1][y1];
	Piece& dst = board[x2][y2];
	if (src.color != turn) {
		cout << "Invalid move: that's not your color" << endl;
		return false;
	}
	if (src.color == dst.color && dst.color != NONE) {
		cout << "Invalid move: cannot land on your own piece" << endl;
		return false;
	}
	if (isValid(src, dst) == false) {
		cout << "Invalid move: " << endl;
		return false;
	}
	else {
		// is finish
		if (dst.type == KING) {
			if (dst.color == WHITE) {
				cout << "Game Over: Black Wins" << endl;
			}
			else {
				cout << "Game Over: White Wins" << endl;
			}
			return true;
		}

		// is not finish
		dst.type = src.type;
		dst.color = src.color;
		src.type = EMPTY;
		src.color = NONE;

		if (turn == WHITE) turn = BLACK;
		else turn = WHITE;

		cout << endl << "[Updated Board]" << endl;
		print();
	}
	return false;
}

bool Board::isValid(const Piece& src, const Piece& dst) const {
    switch (src.type) {
        case KING: return isValidKing(src, dst); break;
        case QUEEN: return isValidQueen(src, dst); break;
        case BISHOP: return isValidBishop(src, dst); break;
        case KNIGHT: return isValidKnight(src, dst); break;
        case ROOK: return isValidRook(src, dst); break;
        case PAWN: return isValidPawn(src, dst); break;
        case EMPTY: return false; break;
        default: break;
    }
	return true;
}

bool Board::isValidKing(const Piece& src, const Piece& dst) const {
	if (abs(dst.x - src.x) == 1 && abs(dst.y - src.y) == 1) 
        return true;
	return false;
}
bool Board::isValidQueen(const Piece& src, const Piece& dst) const{
	int yIncrement;
	int xIncrement;

	if (src.x != dst.x || src.y != dst.y)
	{

		if (src.x == dst.x)
		{
			yIncrement = (dst.y - src.y) / (abs(dst.y - src.y));
			for (int i = src.y + yIncrement; i != dst.y; i += yIncrement)
			{

				if (board[dst.x][i].color != NONE)
					return false;

			}
		}
		else
			if (src.y == dst.y)
			{

				xIncrement = (dst.x - src.x) / (abs(dst.x - src.x));
				for (int i = src.x + xIncrement; i != dst.x; i += xIncrement)
				{
					if (board[i][dst.y].color != NONE)
						return false;
				}
			}
			else
				if (abs(src.x - dst.x) == abs(src.y - dst.y))
				{
					xIncrement = (dst.x - src.x) / (abs(dst.x - src.x));
					yIncrement = (dst.y - src.y) / (abs(dst.y - src.y));

					for (int i = 1; i < abs(src.x - dst.x); i++)
					{
						if (board[src.x + xIncrement*i][src.y + yIncrement*i].color != NONE)
							return false;

					}
				}
				else
					return false;
	}
    return true;
}
bool Board::isValidBishop(const Piece& src, const Piece& dst) const {
	if (abs(src.x - dst.x) == abs(src.y - dst.y))
	{
		int xIncrement = (dst.x - src.x) / (abs(dst.x - src.x));
		int yIncrement = (dst.y - src.y) / (abs(dst.y - src.y));

		for (int i = 1; i < abs(src.x - dst.x); i++)
		{
			if (board[src.x + xIncrement*i][src.y + yIncrement*i].color != NONE)
				return false;

		}
	}
	else
		return false;

    return true;
}
bool Board::isValidKnight(const Piece& src, const Piece& dst) const {
	if ((abs(src.x - dst.x) == 2 && abs(src.y - dst.y) == 1) || (abs(src.x - dst.x) == 1 && abs(src.y - dst.y) == 2)){
        return true;
	}
    return false;
}
bool Board::isValidRook(const Piece& src, const Piece& dst) const {
	if (src.x != dst.x || src.y != dst.y)
	{

		if (src.x == dst.x)
		{
			int yIncrement = (dst.y - src.y) / (abs(dst.y - src.y));
			for (int i = src.y + yIncrement; i != dst.y; i += yIncrement)
			{

				if (board[dst.x][i].color != NONE)
					return false;

			}
		}
		else
			if (src.y == dst.y)
			{

				int xIncrement = (dst.x - src.x) / (abs(dst.x - src.x));
				for (int i = src.x + xIncrement; i != dst.x; i += xIncrement)
				{
					if (board[i][dst.y].color != NONE)
						return false;
				}
			}
			else
				return false;
	}
    return true;
}
bool Board::isValidPawn(const Piece& src, const Piece& dst) const {
    if (src.color == WHITE) {
		if (src.x == dst.x + 1 && src.y == dst.y && dst.color == NONE) {
			return true;
		}
		if (abs(src.y - dst.y) == 1 && src.x == dst.x + 1 && dst.color == BLACK) {
			return true;
		}
		// first 2 step jump
		if (src.x == 6 && src.x == dst.x + 2 && src.y == dst.y && dst.color == NONE) {
			return true;
		}
		return false;
	}
	if (src.color == BLACK) {
		if (src.x == dst.x - 1 && src.y == dst.y && dst.color == NONE) {
			return true;
		}
		if (abs(src.y - dst.y) == 1 && src.x == dst.x - 1 && dst.color == WHITE) {
			return true;
		}
		// first 2 step jump
		if (src.x == 1 && src.x == dst.x - 2 && src.y == dst.y && dst.color == NONE) {
			return true;
		}
		return false;
	}
	return false;
}

bool Board::isUnderAttack(const Piece& dst) const {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			const Piece& src = board[i][j];
			if (isEnemy(board[i][j], dst) && isValid(board[i][j], dst)) {
				return true;
			}
		}
	}
	return false;
}

double Board::score() const {
	double total = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			const Piece& src = board[i][j]; 
			if (src.color == turn) {
				switch(board[i][j].type) {
					case KING: total += (isUnderAttack(src) ? 1000.0 / 2 : 1000.0); break;
					case QUEEN: total += (isUnderAttack(src) ? 9.0 / 2 : 9.0); break;
					case BISHOP: total += (isUnderAttack(src) ? 3.0 / 2 : 3.0); break;
					case KNIGHT: total += (isUnderAttack(src) ? 3.0 / 2 : 3.0); break;
					case ROOK: total += (isUnderAttack(src) ? 5.0 / 2 : 5.0); break;
					case PAWN: total += (isUnderAttack(src) ? 1.0 / 2 : 1.0); break;
					case EMPTY: break;
				}
			}
		}
	}
	return total;
}


void Board::suggest() {
	double it = 0;
	double max = 0;
	int x1, y1, x2, y2;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].color == turn) {
				Piece& src = board[i][j];
				for (int m = 0; m < 8; m++) {
					for (int n = 0; n < 8; n++) {
						Piece& dst = board[m][n];
						if (isValid(src, dst)) {
							Piece tmp(dst.type, dst.color);
							dst.type = src.type;
							dst.color = src.color;
							src.type = EMPTY;
							src.color = NONE;
							it = score();
							if (it > max) {
								x1 = i;
								y1 = j;
								x2 = m;
								y2 = n;
								max = it;
							}
							src.type = dst.type;
							src.color = dst.color;
							dst.type = tmp.type;
							dst.color = tmp.color;
						}
					}
				}
			}
		}
	}
	char notation[5];
	notation[0] = 'a' + y1;
	notation[1] = '8' - x1;
	notation[2] = 'a' + y2;
	notation[3] = '8' - x2;
	notation[4] = '\0';
	cout << "suggestion is " << notation << endl;
}

bool Board::save() const {
	ofstream outFile("save.txt");
	if (!outFile.is_open()) {
		std::cerr << "Unable to open file!" << std::endl;
		return false;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			outFile << board[i][j].getSymbol() << ' ';
		}
    	outFile << '\n'; // Move to the next line after each row
  	}
	return true;
}

bool Board::load() {
	// Open the file for reading
    std::ifstream inFile("save.txt");

    // Check if the file is open
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }
		
	// Read the matrix from the file
	char symbol;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!(inFile >> symbol)) {
                std::cerr << "Error reading from file!" << std::endl;
                inFile.close();
                return false;
            }
			board[i][j].type = Piece::getTypeFromSymbol(symbol);
			board[i][j].color = Piece::getColorFromSymbol(symbol);
        }
    }

    // Close the file
    inFile.close();
	return true;
}