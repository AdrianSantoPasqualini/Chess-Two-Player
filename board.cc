#include "board.h"
#include "square.h"
#include "piece.h"
using namespace std;

ostream & operator<<(ostream &out, const Board &b) {
	for (int i = 0; i < 8; ++i) {
		out << 8 - i << " ";
		for (int j = 0; j < 8; ++j) {
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
	out << endl <<  "  abcdefgh" << endl;
	return out;
	
}

void Board::init() {

	whitesTurn = true;
	squares.clear();
	for (int c = 0; c < 8; c++) {
		vector<Square> columns = {};
		squares.emplace_back(columns);
		for (int r = 0; r < 8; r++) {
			Square s = Square(r, c, nullptr);
			squares[c].emplace_back(s);
		}
	}

	shared_ptr<Piece> rook1b = make_shared<Rook>(0, 0, false, "r1", 0);
	squares[0][0].setPiece(rook1b);
	shared_ptr<Piece> knight1b = make_shared<Knight>(0, 1, false, "n1", 0);
        squares[0][1].setPiece(knight1b);
	shared_ptr<Piece> bishop1b = make_shared<Bishop>(0, 2, false, "b1", 0);
        squares[0][2].setPiece(bishop1b);
	shared_ptr<Piece> queenb = make_shared<Queen>(0, 3, false, "q", 0);
        squares[0][3].setPiece(queenb);
	shared_ptr<Piece> kingb = make_shared<King>(0, 4, false, "k", 0);
        squares[0][4].setPiece(kingb);
	shared_ptr<Piece> bishop2b = make_shared<Bishop>(0, 5, false, "b2", 0);
        squares[0][5].setPiece(bishop2b);
	shared_ptr<Piece> knight2b = make_shared<Knight>(0, 6, false, "n2", 0);
        squares[0][6].setPiece(knight2b);
	shared_ptr<Piece> rook2b = make_shared<Rook>(0, 7, false, "r2", 0);
        squares[0][7].setPiece(rook2b);
	for (int i = 0; i < 8; i ++) {
		shared_ptr<Piece> pawnb = make_shared<Rook>(1, i, false, "p" + to_string(i), 0);
        	squares[1][i].setPiece(pawnb);
	}

	shared_ptr<Piece> rook1w = make_shared<Rook>(7, 0, true, "R1", 0);
        squares[7][0].setPiece(rook1w);
        shared_ptr<Piece> knight1w = make_shared<Knight>(7, 1, true, "N1", 0);
        squares[7][1].setPiece(knight1w);
        shared_ptr<Piece> bishop1w = make_shared<Bishop>(7, 2, true, "B1", 0);
        squares[7][2].setPiece(bishop1w);
        shared_ptr<Piece> queenw = make_shared<Queen>(7, 3, true, "Q", 0);
        squares[7][3].setPiece(queenw);
        shared_ptr<Piece> kingw = make_shared<King>(7, 4, true, "K", 0);
        squares[7][4].setPiece(kingw);
        shared_ptr<Piece> bishop2w = make_shared<Bishop>(7, 5, true, "B2", 0);
        squares[7][5].setPiece(bishop2w);
        shared_ptr<Piece> knight2w = make_shared<Knight>(7, 6, true, "N2", 0);
        squares[7][6].setPiece(knight2w);
        shared_ptr<Piece> rook2w = make_shared<Rook>(7, 7, true, "R2", 0);
        squares[7][7].setPiece(rook2w);
        for (int i = 0; i < 8; i ++) {
                shared_ptr<Piece> pawnw = make_shared<Rook>(6, i, true, "P" + to_string(i), 0);
                squares[6][i].setPiece(pawnw);
        }

}

void Board::setPlayer(string colour, shared_ptr<Player> player) {
	if (colour == "white") {
		player1 = player;
	} else if (colour == "black") {
		player2 = player;
	}
}
