#include "board.h"
using namespace std;

ostream & operator<<(ostream &out, const Board &b) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece piece = b.squares[i][j].currPiece;
			if (piece == nullptr) {
				if ((i + j) % 2 == 0) {
					out << " ";
				} else {
					out << "-";
				}
			} else {
				out << piece->id[0];
			}
		}
		out << endl;
	}
	return out;
}

void Board::init(string playerOne, string playerTwo) {
	whitesTurn = true;
	squares.clear();
	for (int r = 0; i < 8; i++) {
		for (int c = 0; c < 8; c++) {
			squares[r].emplace_back(Square(r,c));
		}
	}
}
