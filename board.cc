#include "board.h"
#include "square.h"
#include "piece.h"
#include "player.h"
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
		shared_ptr<Piece> pawnb = make_shared<Pawn>(1, i, false, "p" + to_string(i), 0);
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
                shared_ptr<Piece> pawnw = make_shared<Pawn>(6, i, true, "P" + to_string(i), 0);
                squares[6][i].setPiece(pawnw);
        }
}

void Board::setPlayer(string colour, string type) {
	if (colour == "white") {
		if (type == "human") {
			player1 = make_unique<Human>(true);
		} else if (type == "computer1") {
			player1 = make_unique<Level1>(true);
		} else if (type == "computer2") {
			player1 = make_unique<Level2>(true);
		} else if (type == "computer3") {
			player1 = make_unique<Level3>(true);
		} else if (type == "computer4") {
			player1 = make_unique<Level4>(true);
		}	
	} else if (colour == "black") {
		if (type == "human") {
			player2 = make_unique<Human>(false);
		} else if (type == "computer1") {
			player2 = make_unique<Level1>(false);
		} else if (type == "computer2") {
			player2 = make_unique<Level2>(false);
		} else if (type == "computer3") {
			player2 = make_unique<Level3>(false);
		} else if (type == "computer4") {
			player2 = make_unique<Level4>(false);
		}
	}
}

void Board::movePiece(int curR, int curC, int newR, int newC) {
	if (curR >= 0 && curR < 8 && curC >= 0 && curC < 8 &&
	    newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
	    squares[curR][curC].getPiece() != nullptr) {
		bool pieceOnSq = false;
		bool blocked = false;
		shared_ptr<Piece> piece = squares[curR][curC].getPiece();
		if ((whitesTurn && piece->getIsWhite()) || (!whitesTurn && !piece->getIsWhite())) {
			if (squares[newR][newC].getPiece() != nullptr) {
				pieceOnSq = true;
			}
			int inc1 = 0;
			int inc2 = 0;
			if (curR == newR) {
				inc1 = (newC - curC) / (abs(newC - curC));
				for (int j = curC + inc1; j != newC; j += inc1) {
					if (squares[curR][j].getPiece() != nullptr) {
						blocked = true;
						break;
					}
				}
			} else if (curC == newC) {
				inc1 = (newR - curR) / (abs(newR - curR));
				for (int i = curR + inc1; i != newR; i += inc1) {
					 if (squares[i][curC].getPiece() != nullptr) {
						blocked = true;
						break;
					}
				}
			} else if ((abs(curR - newR) == abs(curC - newC)) && (abs(curR - newR) > 0)) {
				inc1 = (newR - curR) / (abs(newR - curR));
				inc2 = (newC - curC) / (abs(newC - curC));
				for (int i = curR + inc1, j = curC + inc2; i != newR && j != newC; i += inc1, j += inc2) {
					if (squares[i][j].getPiece() != nullptr) {
						blocked = true;
						break;
					}
				}
			}
			try {
				piece->move(newR, newC, pieceOnSq, blocked);
				squares[newR][newC].setPiece(piece);
				squares[curR][curC].setPiece(nullptr);
				cout << *this;
				if (whitesTurn) {
					whitesTurn = false;
				} else {
					whitesTurn = true;
				}
			} catch (string msg) {
				cout << msg << endl;
			}
		} else {
			cout << "Wrong colour piece moved." << endl;
		}
	} else if (squares[curR][curC].getPiece() == nullptr) {
		cout << "There is no piece on the square you are trying to move from." << endl;
	} else {
		cout << "Invalid coordinates." << endl;
	}
}

void Board::incWhiteScore() {
	whiteScore++;
}

void Board::incBlackScore() {
	blackScore++;
}

bool Board::isWhitesTurn() {
	return whitesTurn;
}
