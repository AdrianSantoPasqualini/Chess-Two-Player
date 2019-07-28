#include "window.h"
#include "board.h"
#include "player.h"
#include "info.h"
#include "state.h"

using namespace std;

Board::Board(vector<vector<Square>> squares): squares{squares} {}

Board::Board() {
	whiteScore = 0;
	blackScore = 0;
	defWhitesTurn = true;
	whiteCounts = {1, 1, 2, 2, 2, 8};
	blackCounts = {1, 1, 2, 2, 2, 8};
	for (int r = 0; r < 8; r++) {
		vector<Square> rows = {};
		defSquares.emplace_back(rows);
		for (int c = 0; c < 8; c++) {
			Square s = Square(r, c, nullptr);
			defSquares[r].emplace_back(s);
		}
	}
	shared_ptr<Piece> rook1b = make_shared<Rook>(0, 0, false, "r1", 0);
	defSquares[0][0].setPiece(rook1b);
	shared_ptr<Piece> knight1b = make_shared<Knight>(0, 1, false, "n1", 0);
	defSquares[0][1].setPiece(knight1b);
	shared_ptr<Piece> bishop1b = make_shared<Bishop>(0, 2, false, "b1", 0);
        defSquares[0][2].setPiece(bishop1b);
	shared_ptr<Piece> queenb = make_shared<Queen>(0, 3, false, "q", 0);
        defSquares[0][3].setPiece(queenb);
	shared_ptr<Piece> kingb = make_shared<King>(0, 4, false, "k", 0);
        defSquares[0][4].setPiece(kingb);
	shared_ptr<Piece> bishop2b = make_shared<Bishop>(0, 5, false, "b2", 0);
        defSquares[0][5].setPiece(bishop2b);
	shared_ptr<Piece> knight2b = make_shared<Knight>(0, 6, false, "n2", 0);
        defSquares[0][6].setPiece(knight2b);
	shared_ptr<Piece> rook2b = make_shared<Rook>(0, 7, false, "r2", 0);
        defSquares[0][7].setPiece(rook2b);
	for (int i = 0; i < 8; i ++) {
		shared_ptr<Piece> pawnb = make_shared<Pawn>(1, i, false, "p" + to_string(i + 1), 0);
        	defSquares[1][i].setPiece(pawnb);
	}
	shared_ptr<Piece> rook1w = make_shared<Rook>(7, 0, true, "R1", 0);
        defSquares[7][0].setPiece(rook1w);
        shared_ptr<Piece> knight1w = make_shared<Knight>(7, 1, true, "N1", 0);
        defSquares[7][1].setPiece(knight1w);
        shared_ptr<Piece> bishop1w = make_shared<Bishop>(7, 2, true, "B1", 0);
        defSquares[7][2].setPiece(bishop1w);
        shared_ptr<Piece> queenw = make_shared<Queen>(7, 3, true, "Q", 0);
        defSquares[7][3].setPiece(queenw);
        shared_ptr<Piece> kingw = make_shared<King>(7, 4, true, "K", 0);
        defSquares[7][4].setPiece(kingw);
        shared_ptr<Piece> bishop2w = make_shared<Bishop>(7, 5, true, "B2", 0);
        defSquares[7][5].setPiece(bishop2w);
        shared_ptr<Piece> knight2w = make_shared<Knight>(7, 6, true, "N2", 0);
        defSquares[7][6].setPiece(knight2w);
        shared_ptr<Piece> rook2w = make_shared<Rook>(7, 7, true, "R2", 0);
        defSquares[7][7].setPiece(rook2w);
        for (int i = 0; i < 8; i++) {
                shared_ptr<Piece> pawnw = make_shared<Pawn>(6, i, true, "P" + to_string(i + 1), 0);
                defSquares[6][i].setPiece(pawnw);
	}
}

void Board::draw() {
	window.drawString(90, 570, "a", 1);
	window.drawString(150, 570, "b", 1);
	window.drawString(210, 570, "c", 1);
	window.drawString(270, 570, "d", 1);
	window.drawString(330, 570, "e", 1);
	window.drawString(390, 570, "f", 1);
	window.drawString(450, 570, "g", 1);
	window.drawString(510, 570, "h", 1);
	window.drawString(30, 90, "8", 1);
	window.drawString(30, 150, "7", 1);
	window.drawString(30, 210, "6", 1);
	window.drawString(30, 270, "5", 1);
	window.drawString(30, 330, "4", 1);
	window.drawString(30, 390, "3", 1);
	window.drawString(30, 450, "2", 1);
	window.drawString(30, 510, "1", 1);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i%2 == 0) {
				if (j%2 == 0) {
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, 0);	
				} else { 
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, 1);	
				}
			} else {
				if (j%2 == 0) {
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, 1);	
				} else { 
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, 0);	
				}
			}
			if (defSquares[i][j].getInfo().piece != nullptr) {
				drawPiece(defSquares[i][j].getInfo().piece);
			}
		}	
	}
}

void Board::drawScore() {

}

void Board::drawPiece(shared_ptr<Piece> piece) {
	pair<int, int> coords = piece->getCoor();
	int r = coords.first;
	int c = coords.second;
	int colour = piece->getIsWhite() ? 4 : 11;
	char id = toupper(piece->getId().at(0));
	if (id == 'K') {
		window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);	
		window.fillRectangle(c*60 + 75, r*60 + 80, 30, 10, colour);	
		window.fillRectangle(c*60 + 85, r*60 + 70, 10, 30, colour);
	} else if (id == 'Q') {
		window.fillCircle(c*60 + 90, r*60 + 90, 30, colour);	
	} else if (id == 'B') {
		window.fillCircle(c*60 + 90, r*60 + 90, 30, colour);	
	} else if (id == 'R') {
		window.fillCircle(c*60 + 90, r*60 + 90, 30, colour);	
	} else if (id == 'N') {
		window.fillCircle(c*60 + 90, r*60 + 90, 30, colour);	
	} else if (id == 'P') {
		window.fillCircle(c*60 + 90, r*60 + 80, 20, colour);	
		//window.fillPolygon(c * 60 + 90, r * 60 + 80, 3, 30, 0, colour);
	} 
	//cout << id << " " << r << " " << c << endl;
}

void Board::undrawPiece(int r, int c) {
	if (r%2 == 0) {
		if (c%2 == 0) {
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, 0);	
		} else { 
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, 1);	
		}
	} else {
		if (c%2 == 0) {
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, 1);	
		} else { 
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, 0);	
		}
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

int Board::getWhiteScore() {
	return whiteScore;
}

int Board::getBlackScore() {
	return blackScore;
}

void Board::init() {
	whitesTurn = defWhitesTurn;
	squares.clear();
	squares = defSquares;
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			for (int k = -1; k <= 1; k++) {
				for (int m = -1; m <= 1; m++) {
					if ((!((i+k < 0)||(j+m < 0))) && (!((i+k > 7)||(j+m > 7)))) {
						if (!((k == 0) && ( m == 0))) {
							squares[i][j].attach(&squares[i+k][j+m]);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (squares[i][j].getInfo().piece != nullptr) {
				State nState{StateType::PieceAdded, Direction::N, true, squares[i][j].getInfo().piece, false};
				squares[i][j].setState(nState);
				squares[i][j].notifyObservers();
			}
		}
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
	if (curR >= 0 && curR < 8 && curC >= 0 && curC < 8 && newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && !(curR == newR && curC == newC)) {
		shared_ptr<Piece> curPiece = squares[curR][curC].getInfo().piece;
		Info newInfo;
		if (curPiece != nullptr) {
			bool pieceOnSq = false;
			bool blocked = false;
			bool moveIntoAttack = false;
			bool curWhite = curPiece->getIsWhite();
			if ((whitesTurn && curWhite) || (!whitesTurn && !curWhite)) {
				// Check new square
				newInfo = squares[newR][newC].getInfo();
				if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
					moveIntoAttack = true;
				}
				if (newInfo.piece != nullptr) {
					if (newInfo.piece->getIsWhite() != curWhite) {	
						pieceOnSq = true;
					} else {
						blocked = true;
					}				
				}
				// Check path to new square
				int inc1 = 0;
				int inc2 = 0;
				if (curR == newR) {
					inc1 = (newC - curC) / (abs(newC - curC));
					for (int j = curC + inc1; j != newC; j += inc1) {
						newInfo = squares[curR][j].getInfo();
						if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
							moveIntoAttack = true;
						}
						if (newInfo.piece != nullptr) {
							blocked = true;
							break;
						}
					}
				} else if (curC == newC) {
					inc1 = (newR - curR) / (abs(newR - curR));
					for (int i = curR + inc1; i != newR; i += inc1) {
						newInfo = squares[i][curC].getInfo();
						if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
							moveIntoAttack = true;
						}
						if (newInfo.piece != nullptr) {
							blocked = true;
							break;
						}
					}
				} else if ((abs(curR - newR) == abs(curC - newC)) && (abs(curR - newR) > 0)) {
					inc1 = (newR - curR) / (abs(newR - curR));
					inc2 = (newC - curC) / (abs(newC - curC));
					for (int i = curR + inc1, j = curC + inc2; i != newR && j != newC; i += inc1, j += inc2) {
						newInfo = squares[i][j].getInfo();
						if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
							moveIntoAttack = true;
						}   
						if (newInfo.piece != nullptr) {
							blocked = true;
							break;
						}
					}
				}
				// Move piece
				try {
					curPiece->move(newR, newC, pieceOnSq, blocked, moveIntoAttack);
					shared_ptr<Piece> castledRook;
					// Kingside castling
					if (curPiece->getCastle() == 1) {
						castledRook = squares[curR][curC + 3].getInfo().piece;
						if (castledRook->getMovesMade() == 0) {
							curPiece->updatePiece(newR, newC);
							castledRook->updatePiece(newR, newC - 1);
							squares[newR][newC - 1].setPiece(castledRook);
							squares[curR][curC + 3].setPiece(nullptr);
							updateTurn(curR, curC, newR, newC, curPiece);
						} else {
							cout << "King cannot castle, rook has already moved." << endl;
						}
					// Queenside castling
					} else if (curPiece->getCastle() == 2) {
						castledRook = squares[curR][curC - 4].getInfo().piece;
						if (castledRook->getMovesMade() == 0) {
							curPiece->updatePiece(newR, newC);
							castledRook->updatePiece(newR, newC + 1);
							squares[newR][newC + 1].setPiece(castledRook);
							squares[curR][curC - 4].setPiece(nullptr);
							updateTurn(curR, curC, newR, newC, curPiece);
						} else {
							cout << "King cannot castle, rook has already moved." << endl;
						} 
					} else {
						// Pawn promotion
						if ((curPiece->getId()[0] == 'P' && newR == 0) || (curPiece->getId()[0] == 'p' && newR == 7)) {
							char promotion;
							cin >> promotion;
							if (whitesTurn) {
								while (promotion != 'Q' && promotion != 'N' && promotion != 'R' && promotion != 'B') {
									cout << "Invalid promotion." << endl;
									cin >> promotion;
								}
								if (promotion == 'Q') {
									curPiece = make_shared<Queen>(newR, newC, true, "Q2", curPiece->getMovesMade());
								} else if (promotion == 'N') {
									curPiece = make_shared<Knight>(newR, newC, true, "N3", curPiece->getMovesMade());
								} else if (promotion == 'R') {
									curPiece = make_shared<Rook>(newR, newC, true, "R3", curPiece->getMovesMade());
								} else if (promotion == 'B') {
									curPiece = make_shared<Bishop>(newR, newC, true, "B3", curPiece->getMovesMade());
								}
							} else {
								while (promotion != 'q' && promotion != 'n' && promotion != 'r' && promotion != 'b') {
									cout << "Invalid promotion." << endl;
									cin >> promotion;
								}
								if (promotion == 'q') {
									curPiece = make_shared<Queen>(newR, newC, false, "q2", curPiece->getMovesMade());
								} else if (promotion == 'n') {
									curPiece = make_shared<Knight>(newR, newC, false, "n3", curPiece->getMovesMade());
								} else if (promotion == 'r') {
									curPiece = make_shared<Rook>(newR, newC, false, "r3", curPiece->getMovesMade());
								} else if (promotion == 'b') {
									curPiece = make_shared<Bishop>(newR, newC, false, "b3", curPiece->getMovesMade());
								}		
							}
						}
						bool remove = false;
						if (pieceOnSq) {
							if (whitesTurn && !squares[newR][newC].getInfo().piece->getIsWhite()) {
								remove = true;
							} else if (!whitesTurn && squares[newR][newC].getInfo().piece->getIsWhite()) {
								remove = true;
							}
						}
						updateTurn(curR, curC, newR, newC, curPiece);
					}
					curPiece->changeCastle(0);
				} catch (string msg) {
					cout << msg << endl;
				}
			} else {
				cout << "Wrong colour piece moved." << endl;
			}
		} else {
			cout << "There is no piece on the square you are trying to move from." << endl;
		}
	} else {
		cout << "Invalid coordinates." << endl;
	}
}

void Board::updateTurn(int curR, int curC, int newR, int newC, shared_ptr<Piece> piece) {	
	squares[curR][curC].setPiece(nullptr);	
	State rState{StateType::PieceRemoved, Direction::N, false, piece, false};
	squares[curR][curC].setState(rState);
	squares[curR][curC].notifyObservers();
	if (squares[newR][newC].getInfo().piece != nullptr) {
		State mState{StateType::PieceRemoved, Direction::N, false,  squares[newR][newC].getInfo().piece, false};
		squares[newR][newC].setState(mState);
		squares[newR][newC].notifyObservers();
	}
	squares[newR][newC].setPiece(piece);

	drawPiece(piece);
	undrawPiece(curR, curC);

	State nState{StateType::PieceAdded, Direction::N, true, piece, false};
	squares[newR][newC].setState(nState);
	squares[newR][newC].notifyObservers();

	cout << *this;
	if (whitesTurn) {
		whitesTurn = false;
	} else {
		whitesTurn = true;
	}
}


void Board::printDefault() {
	for (int i = 0; i < 8; ++i) {
		cout << 8 - i << " ";
		for (int j = 0; j < 8; ++j) {
			shared_ptr<Piece> piece = (defSquares[i][j]).getInfo().piece;
			if (piece == nullptr) {
				if ((i + j) % 2 == 0) {
					cout << " ";
				} else {
					cout << "-";
				}
			} else {
				cout << piece->getId()[0];
			}
		}
		cout << endl;
	}
	cout << endl <<  "  abcdefgh" << endl;
}
	

void Board::setup() {
	printDefault();
	vector<char> validPieces = {'K', 'Q', 'B', 'R', 'N', 'P', 'k', 'q', 'b', 'r', 'n', 'p'};
	bool done = false;
		while (!done) {
		try {
			string cmd;
			cin >> cmd;
			if (cmd == "+") {
				char piece;
				char col;
				int row;
				shared_ptr<Piece> p;
				cin >> piece >> col >> row;
				if (col < 'a' || col > 'h') {
					string e = "Column not in range.";
					throw e;	
				} else if (row < 1 || row > 8) {
					string e = "Row not in range.";
					throw e;
				}
				// check that piece is a valid piece
				vector<char>::iterator it;
				it = find(validPieces.begin(), validPieces.end(), piece);
				if (it == validPieces.end()) {
					string e = "Given piece is not valid.";
					throw e;
				}
				if (piece == 'K' && whiteCounts[0] == 0) {
					p = make_shared<King>(8 - row, col - 'a', true, "K", 0);
					whiteCounts[0]++;
				} else if (piece == 'Q' && whiteCounts[1] == 0) {
					p = make_shared<Queen>(8 - row, col - 'a', true, "Q", 0);
					whiteCounts[1]++;
				} else if (piece == 'B' && whiteCounts[2] < 2) {
					p = make_shared<Bishop>(8 - row, col - 'a', true, "B" + to_string(whiteCounts[2]), 0);
					whiteCounts[2]++;
				} else if (piece == 'R' && whiteCounts[3] < 2) {
					p = make_shared<Rook>(8 - row, col - 'a', true, "R" + to_string(whiteCounts[3]), 0);
					whiteCounts[3]++;
				} else if (piece == 'N' && whiteCounts[4] < 2) {
					p = make_shared<Knight>(8 - row, col - 'a', true, "N" + to_string(whiteCounts[4]), 0);
					whiteCounts[4]++;
				} else if (piece == 'P' && whiteCounts[5] < 8) {
					if (row == 1 || row == 8) {
						string e = "Pawn cannot be on the first or last row of the board.";
						throw e;
					}
					p = make_shared<Pawn>(8 - row, col - 'a', true, "P" + to_string(whiteCounts[5]), 0);
					whiteCounts[5]++;
				} else if (piece == 'k' && blackCounts[0] == 0) {
					p = make_shared<King>(8 - row, col - 'a', false, "k", 0);
					blackCounts[0]++;
				} else if (piece == 'q' && blackCounts[1] == 0) {
					p = make_shared<Queen>(8 - row, col - 'a', false, "q", 0);
					blackCounts[1]++;
				} else if (piece == 'b' && blackCounts[2] < 2) {
					p = make_shared<Bishop>(8 - row, col - 'a', false, "b" + to_string(blackCounts[2]), 0);
					blackCounts[2]++;
				} else if (piece == 'r' && blackCounts[3] < 2) {
					p = make_shared<Rook>(8 - row, col - 'a', false, "r" + to_string(blackCounts[3]), 0);
					blackCounts[3]++;
				} else if (piece == 'n' && blackCounts[4] < 2) {
					p = make_shared<Knight>(8 - row, col - 'a', false, "n" + to_string(blackCounts[4]), 0);
					blackCounts[4]++;
				} else if (piece == 'p' && blackCounts[5] < 8) {
					if (row == 1 || row == 8) {
						string e = "Pawn cannot be on the first or last row of the board.";
						throw e;
					}
					p = make_shared<Pawn>(8 - row, col - 'a', false, "p" + to_string(blackCounts[5]), 0);
					blackCounts[5]++;
				} else { 
					string e = "Given piece is already on the board.";
					throw e;
				}
				defSquares[8 - row][col - 'a'].setPiece(p);
				printDefault();
				drawPiece(p);
			} else if (cmd == "-") {
				char col;
				int row;	
				cin >> col >> row;
				if (col < 'a' || col > 'h') {
					string e = "Column not in range.";
					throw e;	
				} else if (row < 1 || row > 8) {
					string e = "Row not in range.";
					throw e;	
				}
				shared_ptr<Piece> p = defSquares[8 - row][col - 'a'].getInfo().piece;
				if (p) {
					string id = p->getId();
					char piece = id.at(0);
					switch(piece) {
						case 'K': 
							whiteCounts[0]--;
							break;	
						case 'Q': 
							whiteCounts[1]--;
							break;
						case 'B': 
							whiteCounts[2]--;
							break;
						case 'R': 
							whiteCounts[3]--;
							break;
						case 'N': 
							whiteCounts[4]--;
							break;
						case 'P': 
							whiteCounts[5]--;
							break;
						case 'k': 
							blackCounts[0]--;
							break;
						case 'q': 
							blackCounts[1]--;
							break;
						case 'b': 
							blackCounts[2]--;
							break;
						case 'r': 
							blackCounts[3]--;
							break;
						case 'n': 
							blackCounts[4]--;
							break;
						case 'p': 
							blackCounts[5]--;
							break;
						default: break;
					}
					defSquares[8 - row][col - 'a'].setPiece(nullptr);
					undrawPiece(8-row, col-'a');
					printDefault();
				}
			} else if (cmd == "=") {
				string player;
				cin >> player;
				if (player == "white") {
					defWhitesTurn = true;
				} else if (player == "black") {
					defWhitesTurn = false;
				} else {
					cout << "Options are white or black." << endl;
				}
			} else if (cmd == "done") {
				if (whiteCounts[0] == 0 || blackCounts[0] == 0) {
					cout << "Both kings must be on the board." << endl;
				// add checks to make sure neither player is in check	
				} else {
					done = true;
				}
			} else {
				cout << "Please enter a valid command." << endl;
			}	
		} catch (string e) {
			cout << e << endl;
		} catch (...) { 
			cin.clear();
			cin.ignore();
		}
	} 
}

ostream & operator<<(ostream &out, const Board &b) {
	for (int i = 0; i < 8; ++i) {
		out << 8 - i << " ";
		for (int j = 0; j < 8; ++j) {
			
			/*
			Info info = b.squares[i][j].getInfo();
			
			if (info.wAttacked || info.bAttacked) {
				cout << "A";
			} else {
				cout << " ";
			}
			*/
			
			shared_ptr<Piece> piece = (b.squares[i][j]).getInfo().piece;
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
