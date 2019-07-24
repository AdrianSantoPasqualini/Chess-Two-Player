#include "board.h"
#include "square.h"
#include "piece.h"
using namespace std;

ostream & operator<<(ostream &out, const Board &b) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Piece * piece = (b.squares[i][j]).getPiece();
			if (piece == nullptr) {
				if ((i + j) % 2 == 0) {
					out << " ";
				} else {
					out << "-";
				}
			} else {
				out << piece->getId()[0];
			}
		}
		out << endl;
	}
	return out;
}

void Board::init(string playerOne, string playerTwo) {
	whitesTurn = true;
	squares.clear();
	for (int c = 0; c < 8; c++) {
		vector<Square> columns = {};
		squares.emplace_back(columns);
		for (int r = 0; r < 8; r++) {
			Square s = Square(r,c,nullptr);
			squares[c].emplace_back(s);
		}
	}
}



int main() {
	Board b;
	b.init("a","b");
	cout << b;

}
