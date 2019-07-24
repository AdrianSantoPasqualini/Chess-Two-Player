#include "board.h"
using namespace std;

ostream & operator<<(ostream &out, const Board &b) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece piece = b.squares[i][j].currPiece;
			out << piece.id[0];
		}
		out << endl;
	}
	return out;
}
