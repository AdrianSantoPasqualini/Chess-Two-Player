#include "board.h"
#include "square.h"
#include "piece.h"
using namespace std;

ostream & operator<<(ostream &out, const Board &b) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			out << 8 - j << " ";
			shared_ptr<Piece> piece = (b.squares[i][j]).getPiece();
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
	out << "  abcdefgh";
	return out;
}

void Board::init(string playerOne, string playerTwo) {
	whitesTurn = true;
	squares.clear();
	for (int c = 0; c < 8; c++) {
		vector<Square> columns = {};
		squares.emplace_back(columns);
		for (int r = 0; r < 8; r++) {
			shared_ptr<Piece> nPiece;
			Square s = Square(r, c, nPiece);
			squares[c].emplace_back(s);
		}
	}
	shared_ptr<Piece> rook1b = make_shared<Piece>(0, 0, "r1", false, 0);
	squares[0][0].setPiece(rook1b);
	shared_ptr<Piece> knight1b = make_shared<Piece>(0, 1, "n1", false, 0);
        squares[0][1].setPiece(knight1b);
	shared_ptr<Piece> bishop1b = make_shared<Piece>(0, 2, "b1", false, 0);
        squares[0][2].setPiece(bishop1b);
	shared_ptr<Piece> queenb = make_shared<Piece>(0, 3, "q", false, 0);
        squares[0][3].setPiece(queenb);
	shared_ptr<Piece> kingb = make_shared<Piece>(0, 4, "k", false, 0);
        squares[0][4].setPiece(kingb);
	shared_ptr<Piece> bishop2b = make_shared<Piece>(0, 5, "b2", false, 0);
        squares[0][5].setPiece(bishop2b);
	shared_ptr<Piece> knight2b = make_shared<Piece>(0, 6, "n2", false, 0);
        squares[0][6].setPiece(knight2b);
	shared_ptr<Piece> rook2b = make_shared<Piece>(0, 7, "r2", false, 0);
        squares[0][7].setPiece(rook2b);

}

int main() {
	Board b;
	b.init("a","b");
	cout << b;
}
