#include "window.h"
#include "board.h"
#include "player.h"
#include "info.h"
#include "state.h"

using namespace std;

Board::Board(vector<vector<Square>> squares): squares{squares} {}

Board::Board() {
	moves = 0;
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

void Board::generatePlayerMoves(bool white) {
	if (white) {
		player1->generateLegalMoves();
	} else {
		player2->generateLegalMoves();
	}
}

string Board::whoWon() {
	int wLegalMoves = player1->howManyLegalMoves();
	int bLegalMoves = player2->howManyLegalMoves();
	if (wLegalMoves == 0) {
		if (player1->isInCheck()) {
			return "black";
		} else {
			return "stalemate";
		}
		squares.clear();
	} else if (bLegalMoves == 0) {
		if (player2->isInCheck()) {
			return "white";
		} else {
			return "stalemate";
		}
		squares.clear();
	} else {
		return "noone";
	}
	return "noone";
}


void Board::drawMenu() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i%2 == 0) {
				if (j%2 == 0) {
					window.fillRectangle(j*60, i*60, 60, 60, 0);	
				} else { 
					window.fillRectangle(j*60, i*60, 60, 60, 1);	
				}
			} else {
				if (j%2 == 0) {
					window.fillRectangle(j*60, i*60, 60, 60, 1);	
				} else { 
					window.fillRectangle(j*60, i*60, 60, 60, 0);	
				}
			}
		}	
	}
	window.fillRectangle(100, 130, 400, 200, 0);
	window.drawString(280, 200, "CHESS", 1);
	window.drawString(150, 230, "<game> <white-player> <black-player> to start a game!", 1); 
	window.drawString(170, 250, "players can be one of: human computer1 computer2", 1);
	window.drawString(320, 270, "computer3 computer4", 1);
	window.drawString(150, 300, "<setup> to set up the board!", 1); 
	
	/*		
	window.fillRectangle(60 + 75, 60 + 100, 30, 10, colour);	
	window.fillRectangle(60 + 75, 60 + 80, 30, 10, colour);	
	window.fillRectangle(60 + 85, 60 + 70, 10, 30, colour);

	window.fillCircle(c*60 + 89, r*60 + 78, 10, colour);
	window.fillPolygon(c * 60 + 62, r * 60 + 91, 3, 25,0, colour);
	window.fillPolygon(c * 60 + 68, r * 60 + 111, 3, 41,1, colour);
	window.fillPolygon(c * 60 + 90, r * 60 + 91, 3, 25,0, colour);

	window.fillCircle(c*60 + 90, r*60 + 68, 10, colour);
	window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);
	window.fillRectangle(c*60 + 80, r*60 + 85, 20, 20, colour);
	window.fillPolygon(c*60 + 78, r*60 + 87, 3, 25,1, colour);

	window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);	
	window.fillRectangle(c*60 + 80, r*60 + 80, 20, 20, colour);	
	window.fillRectangle(c*60 + 78, r*60 + 75, 6, 10, colour);	
	window.fillRectangle(c*60 + 88, r*60 + 75, 6, 10, colour);	
	window.fillRectangle(c*60 + 97, r*60 + 75, 6, 10, colour);	

	window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);	
	window.fillRectangle(c*60 + 82, r*60 + 80, 15, 20, colour);	
	window.fillPolygon(c*60 + 80, r*60 + 72, 4, 12, -1, colour);
	window.fillPolygon(c*60 + 88, r*60 + 68, 4, 12, -1, colour);
	window.fillPolygon(c*60 + 80, r*60 + 82, 3, 20, 1, colour);

	window.fillCircle(c*60 + 87, r*60 + 77, 15, colour);	
	window.fillPolygon(c * 60 + 87, r * 60 + 77, 3, 30, -1, colour);
	*/	
}

void Board::drawBoard() {
	window.fillRectangle(0, 0, 600, 600, 0);
	int bColour = 9;
	int wColour = 3;
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
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, wColour);	
				} else { 
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, bColour);	
				}
			} else {
				if (j%2 == 0) {
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, bColour);	
				} else { 
					window.fillRectangle(60 + j*60, 60 + i*60, 60, 60, wColour);	
				}
			}
			if (defSquares[i][j].getInfo().piece != nullptr) {
				drawPiece(defSquares[i][j].getInfo().piece);
			}
		}	
	}
}

void Board::drawScore() {
	window.fillRectangle(0, 0, 600, 60, 0);
	string wScore = "White's Score: " + to_string(whiteScore).substr(0,3);
	string bScore = "Black's Score: " + to_string(blackScore).substr(0,3);
	window.drawString(10, 10, wScore, 1);
	//window.drawString(500, 10, bScore, 1);
	window.drawString(485, 10, bScore, 1);
}

void Board::drawTurn() {
	window.fillRectangle(0, 30, 600, 30, 0);
	string turn = whitesTurn ? "White's Turn" : "Black's Turn";
	window.drawString(250, 50, turn, 1);
	if (player1->isInCheck()) {
		window.drawString(350, 50, "-- White is in Check!", 2);
	} else if (player2->isInCheck()) {
		window.drawString(350, 50, "-- Black is in Check!", 2);
	}
}

void Board::drawSetupMenu() {
	window.fillRectangle(0, 0, 600, 60, 0);
	window.drawString(250, 30, "SETUP MODE", 1);
}


void Board::drawPiece(shared_ptr<Piece> piece) {
	pair<int, int> coords = piece->getCoor();
	int r = coords.first;
	int c = coords.second;
	int colour = piece->getIsWhite() ? 0 : 1;
	char id = toupper(piece->getId().at(0));
	if (id == 'K') {
		window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);	
		window.fillRectangle(c*60 + 75, r*60 + 80, 30, 10, colour);	
		window.fillRectangle(c*60 + 85, r*60 + 70, 10, 30, colour);
	} else if (id == 'Q') {
		window.fillCircle(c*60 + 89, r*60 + 78, 10, colour);
		window.fillPolygon(c * 60 + 62, r * 60 + 91, 3, 25,0, colour);
		window.fillPolygon(c * 60 + 68, r * 60 + 111, 3, 41,1, colour);
		window.fillPolygon(c * 60 + 90, r * 60 + 91, 3, 25,0, colour);
	} else if (id == 'B') {
		window.fillCircle(c*60 + 90, r*60 + 68, 10, colour);
		window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);
		window.fillRectangle(c*60 + 80, r*60 + 85, 20, 20, colour);
		window.fillPolygon(c*60 + 78, r*60 + 87, 3, 25,1, colour);
	} else if (id == 'R') {
		window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);	
		window.fillRectangle(c*60 + 80, r*60 + 80, 20, 20, colour);	
		window.fillRectangle(c*60 + 78, r*60 + 75, 6, 10, colour);	
		window.fillRectangle(c*60 + 88, r*60 + 75, 6, 10, colour);	
		window.fillRectangle(c*60 + 97, r*60 + 75, 6, 10, colour);	
	} else if (id == 'N') {
		window.fillRectangle(c*60 + 75, r*60 + 100, 30, 10, colour);	
		window.fillRectangle(c*60 + 82, r*60 + 80, 15, 20, colour);	
		window.fillPolygon(c*60 + 80, r*60 + 72, 4, 12, -1, colour);
		window.fillPolygon(c*60 + 88, r*60 + 68, 4, 12, -1, colour);
		window.fillPolygon(c*60 + 80, r*60 + 82, 3, 20, 1, colour);

	} else if (id == 'P') {
		window.fillCircle(c*60 + 87, r*60 + 77, 15, colour);	
		window.fillPolygon(c * 60 + 87, r * 60 + 77, 3, 30, -1, colour);
	} 
}

void Board::undrawPiece(int r, int c) {
	int wColour = 3;
	int bColour = 9;
	if (r%2 == 0) {
		if (c%2 == 0) {
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, wColour);	
		} else { 
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, bColour);	
		}
	} else {
		if (c%2 == 0) {
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, bColour);	
		} else { 
			window.fillRectangle(60 + c*60, 60 + r*60, 60, 60, wColour);	
		}
	}
}

void Board::incScore(double w, double b) {
	whiteScore += w;
	blackScore += b;
}

bool Board::isWhitesTurn() {
	return whitesTurn;
}

pair<int,int> Board::getScore() {
	return make_pair(whiteScore, blackScore);
}

void Board::makePlayerMove() {
	if (isWhitesTurn()) {
		player1->makeMove();
	} else {
		player2->makeMove();
	}
}

pair<int,int> Board::getAttacks(int r, int c) {
	return make_pair(squares[r][c].getInfo().wTotAttacks, squares[r][c].getInfo().bTotAttacks);
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
//	player1->clearPieces();
//	player2->clearPieces();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (squares[i][j].getInfo().piece != nullptr) {
//				if (squares[i][j].getInfo().piece->getIsWhite()) {
//					player1->addPiece(squares[i][j].getInfo().piece);
//				} else {
//					player2->addPiece(squares[i][j].getInfo().piece);
//				}
				State nState{StateType::PieceAdded, Direction::N, true, squares[i][j].getInfo().piece, false};
				squares[i][j].setState(nState);
				squares[i][j].notifyObservers();
			}
		}
	}
	player1->clearPieces();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (squares[i][j].getInfo().piece != nullptr) {
				string id = squares[i][j].getInfo().piece->getId();
				if (id[0] == 'K' || id[0] == 'B' || id[0] == 'R' || id[0] == 'Q' || id[0] == 'N' || id[0] == 'P') {
					player1->addPiece(squares[i][j].getInfo().piece); 
				}
			}
		}
	}
	player2->clearPieces();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (squares[i][j].getInfo().piece != nullptr) {
				string id = squares[i][j].getInfo().piece->getId();
				if (id[0] == 'k' || id[0] == 'b' || id[0] == 'r' || id[0] == 'q' || id[0] == 'n' || id[0] == 'p') {
					player2->addPiece(squares[i][j].getInfo().piece); 
				}
			}
		}
	}

}

void Board::setPlayer(string colour, string type) {
	if (colour == "white") {
		if (type == "human") {
			player1 = make_shared<Human>(true);
		} else if (type == "computer1") {
			player1 = make_shared<Level1>(true);
		} else if (type == "computer2") {
			player1 = make_shared<Level2>(true);
		} else if (type == "computer3") {
			player1 = make_shared<Level3>(true);
		} else if (type == "computer4") {
			player1 = make_shared<Level4>(true);
		}
		player1->attachBoard(this);
	} else if (colour == "black") {
		if (type == "human") {
			player2 = make_shared<Human>(false);
		} else if (type == "computer1") {
			player2 = make_shared<Level1>(false);
		} else if (type == "computer2") {
			player2 = make_shared<Level2>(false);
		} else if (type == "computer3") {
			player2 = make_shared<Level3>(false);
		} else if (type == "computer4") {
			player2 = make_shared<Level4>(false);
		}	
		player2->attachBoard(this);
	}
}

void Board::movePiece(int curR, int curC, int newR, int newC) {
	if (curR >= 0 && curR < 8 && curC >= 0 && curC < 8 && newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && !(curR == newR && curC == newC)) {
		shared_ptr<Piece> curPiece = squares[curR][curC].getInfo().piece;
		Info newInfo;
		/////////////////// Get rid of new;
		if (curPiece != nullptr) {
			bool pieceOnSq = false;
			bool blocked = false;
			bool moveIntoAttack = false;
			bool checked = false;
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
				// Check if square is under attack (for king)
				newInfo = squares[curR][curC].getInfo();
				if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
					checked = true;
				}
				// Move piece
				try {
					curPiece->move(newR, newC, moves, pieceOnSq, blocked, moveIntoAttack, checked);
					curPiece->updatePiece(newR, newC);
					shared_ptr<Piece> castledRook = nullptr;
					// Kingside castling
					if (curPiece->getCastle() == 1) {
						castledRook = squares[curR][curC + 3].getInfo().piece;
						if (castledRook->getMovesMade() == 0) {
							undrawPiece(curR, curC+3);
							castledRook->updatePiece(newR, newC - 1);
							squares[curR][curC + 3].setPiece(nullptr);
							State rState{StateType::PieceRemoved, Direction::N, false, castledRook, false};
							squares[curR][curC + 3].setState(rState);
							squares[curR][curC + 3].notifyObservers();
							squares[newR][newC - 1].setPiece(castledRook);
							State nState{StateType::PieceAdded, Direction::N, true, castledRook, false};
							squares[newR][newC - 1].setState(nState);
							squares[newR][newC - 1].notifyObservers();
							drawPiece(castledRook);
							updateTurn(curR, curC, newR, newC, curPiece);
						} else {
							cout << "King cannot castle, rook has already moved." << endl;
						}
					// Queenside castling
					} else if (curPiece->getCastle() == 2) {
						castledRook = squares[curR][curC - 4].getInfo().piece;
						if (castledRook->getMovesMade() == 0) {
							undrawPiece(curR, curC-4);
							castledRook->updatePiece(newR, newC + 1);
							squares[curR][curC - 4].setPiece(nullptr);
							State rState{StateType::PieceRemoved, Direction::N, false, castledRook, false};
							squares[curR][curC - 4].setState(rState);
							squares[curR][curC - 4].notifyObservers();
							squares[newR][newC + 1].setPiece(castledRook);
							State nState{StateType::PieceAdded, Direction::N, true, castledRook, false};
							squares[newR][newC + 1].setState(nState);
							squares[newR][newC + 1].notifyObservers();
							drawPiece(castledRook);
							updateTurn(curR, curC, newR, newC, curPiece);
						} else {
							cout << "King cannot castle, rook has already moved." << endl;
						} 
					// En passant
					} else if (curPiece->getEnPassant() == moves - 1 && moves > 3) {
						updateTurn(curR, curC, newR, newC, curPiece);
						// Remove opponent's piece
						int row;
						if (whitesTurn) {
							row = newR - 1;
						} else {
							row = newR + 1;
						}
						shared_ptr<Piece> attackedPiece = squares[row][newC].getInfo().piece;
						State mState{StateType::PieceRemoved, Direction::N, false, attackedPiece, false};
						squares[row][newC].setState(mState);
						squares[row][newC].notifyObservers();
						if (whitesTurn) {
							player2->removePiece(attackedPiece->getId());
						} else {
							player1->removePiece(attackedPiece->getId());
						}
						squares[row][newC].setPiece(nullptr);
						undrawPiece(row, newC);
						// Detect check
						if (whitesTurn) {
							if (player2->isInCheck()) {
								curPiece->updatePiece(curR, curC);
								updateTurn(newR, newC, curR, curC, curPiece);
								curPiece->decrementMoves(2);
								moves -= 2;
								// Update twice to reset turn
								updateTurn(row, newC, row, newC, attackedPiece);
								updateTurn(row, newC, row, newC, attackedPiece);
								attackedPiece->decrementMoves(2);
								player1->addPiece(attackedPiece);
								moves -= 2;
								cout << "Invalid, king is under check after this move." << endl;
							} else if (player1->isInCheck()) {
								cout << "White is in check." << endl;
							}
						} else {						
							if (player1->isInCheck()) {
								curPiece->updatePiece(curR, curC);
								updateTurn(newR, newC, curR, curC, curPiece);
								curPiece->decrementMoves(2);
								moves -= 2;
								// Update twice to reset turn
								updateTurn(row, newC, row, newC, attackedPiece);
								updateTurn(row, newC, row, newC, attackedPiece);
								attackedPiece->decrementMoves(2);
								player2->addPiece(attackedPiece);
								moves -= 2;
								cout << "Invalid, king is under check after this move." << endl;
							} else if (player2->isInCheck()) {
								cout << "Black is in check." << endl;
							}
						}
					} else {
						// Pawn promotion
						char promotion = '0';
						if ((curPiece->getId()[0] == 'P' && newR == 0) || (curPiece->getId()[0] == 'p' && newR == 7)) {
							cin >> promotion;
							if (whitesTurn) {
								while (promotion != 'Q' && promotion != 'N' && promotion != 'R' && promotion != 'B') {
									cout << "Enter a valid promotion piece." << endl;
									cin >> promotion;
								}
								// Change pawn to promoted piece
								State rState{StateType::PieceRemoved, Direction::N, false, curPiece, false};
								squares[curR][curC].setState(rState);
								squares[curR][curC].notifyObservers();
								player1->removePiece(curPiece->getId());
								if (promotion == 'Q') {
									curPiece = make_shared<Queen>(newR, newC, true, "Q2" + curPiece->getId(), curPiece->getMovesMade());
								} else if (promotion == 'N') {
									curPiece = make_shared<Knight>(newR, newC, true, "N3" + curPiece->getId(), curPiece->getMovesMade());
								} else if (promotion == 'R') {
									curPiece = make_shared<Rook>(newR, newC, true, "R3" + curPiece->getId(), curPiece->getMovesMade());
								} else if (promotion == 'B') {
									curPiece = make_shared<Bishop>(newR, newC, true, "B3" + curPiece->getId(), curPiece->getMovesMade());
								}
								player1->addPiece(curPiece);
								State nState{StateType::PieceAdded, Direction::N, true, curPiece, false};
								squares[curR][curC].setState(nState);
								squares[curR][curC].notifyObservers();
							} else {
								while (promotion != 'q' && promotion != 'n' && promotion != 'r' && promotion != 'b') {
									cout << "Enter a valid promotion piece." << endl;
									cin >> promotion;
								}
								// Change pawn to promoted piece
								State rState{StateType::PieceRemoved, Direction::N, false, curPiece, false};
								squares[curR][curC].setState(rState);
								squares[curR][curC].notifyObservers();
								player2->removePiece(curPiece->getId());
								if (promotion == 'q') {
									curPiece = make_shared<Queen>(newR, newC, false, "q2", curPiece->getMovesMade());
								} else if (promotion == 'n') {
									curPiece = make_shared<Knight>(newR, newC, false, "n3", curPiece->getMovesMade());
								} else if (promotion == 'r') {
									curPiece = make_shared<Rook>(newR, newC, false, "r3", curPiece->getMovesMade());
								} else if (promotion == 'b') {
									curPiece = make_shared<Bishop>(newR, newC, false, "b3", curPiece->getMovesMade());
								}
								player2->addPiece(curPiece);
								State nState{StateType::PieceAdded, Direction::N, true, curPiece, false};
								squares[curR][curC].setState(nState);
								squares[curR][curC].notifyObservers();
							}
						}
						// Set up en passant
						if (curPiece->getEnPassant() == moves) {
							shared_ptr<Piece> beside = nullptr;
							if (newC + 1 >= 0 && newC + 1 < 8) {
								beside = squares[newR][newC + 1].getInfo().piece;
							}
							if (beside != nullptr) {
								beside->changeEnPassant(moves);
							}
							if (newC - 1 >= 0 && newC - 1 < 8) {
								beside = squares[newR][newC - 1].getInfo().piece;
							}
							if (beside != nullptr) {
								beside->changeEnPassant(moves);
 							}
						}
						// Move piece
						shared_ptr<Piece> capturedPiece = squares[newR][newC].getInfo().piece;
						updateTurn(curR, curC, newR, newC, curPiece);
						// Detect check
						if (whitesTurn) {
							if (player2->isInCheck()) {
								player2->removePiece(curPiece->getId());
								curPiece->updatePiece(curR, curC);
								if (promotion != '0') {
									State rState{StateType::PieceRemoved, Direction::N, false, curPiece, false};
									squares[newR][newC].setState(rState);
									squares[newR][newC].notifyObservers();
									curPiece = make_shared<Pawn>(curR, curC, false, curPiece->getId().substr(2, 2), curPiece->getMovesMade());
									State nState{StateType::PieceAdded, Direction::N, true, curPiece, false};
									squares[newR][newC].setState(nState);
									squares[newR][newC].notifyObservers();
								}
								player2->addPiece(curPiece);
								// Move pieces back
								updateTurn(newR, newC, curR, curC, curPiece);
								curPiece->decrementMoves(2);
								moves -= 2;
								if (capturedPiece != nullptr) {
									// Update twice to reset turn
									updateTurn(newR, newC, newR, newC, capturedPiece);
									updateTurn(newR, newC, newR, newC, capturedPiece);
									capturedPiece->decrementMoves(2);
									player1->addPiece(capturedPiece);
									moves -= 2;
								}
								cout << "Invalid, king is under check after this move." << endl;
							} else if (player1->isInCheck()) {
								cout << "White is in check." << endl;
							}
						} else {
							if (player1->isInCheck()) {
								player1->removePiece(curPiece->getId());
								curPiece->updatePiece(curR, curC);
								if (promotion != '0') {
									State rState{StateType::PieceRemoved, Direction::N, false, curPiece, false};
									squares[newR][newC].setState(rState);
									squares[newR][newC].notifyObservers();
									curPiece = make_shared<Pawn>(curR, curC, true, curPiece->getId().substr(2, 2), curPiece->getMovesMade());
									State nState{StateType::PieceAdded, Direction::N, true, curPiece, false};
									squares[newR][newC].setState(nState);
									squares[newR][newC].notifyObservers();
								}
								player1->addPiece(curPiece);
								// Move pieces back
								updateTurn(newR, newC, curR, curC, curPiece);
								curPiece->decrementMoves(2);
								moves -= 2;
								if (capturedPiece != nullptr) {
									// Update twice to reset turn
									updateTurn(newR, newC, newR, newC, capturedPiece);
									updateTurn(newR, newC, newR, newC, capturedPiece);
									capturedPiece->decrementMoves(2);
									player2->addPiece(capturedPiece);
									moves -= 2;
								}
								cout << "Invalid, king is under check after this move." << endl;
							} else if (player2->isInCheck()) {
								cout << "Black is in check." << endl;
							}
						}
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
	// Remove piece from current square
	squares[curR][curC].setPiece(nullptr);	
	State rState{StateType::PieceRemoved, Direction::N, false, piece, false};
	squares[curR][curC].setState(rState);
	squares[curR][curC].notifyObservers();
	// Remove captured piece
	shared_ptr<Piece> attackedPiece = squares[newR][newC].getInfo().piece;
	if (attackedPiece != nullptr) {
		State mState{StateType::PieceRemoved, Direction::N, false, attackedPiece, false};
		squares[newR][newC].setState(mState);
		squares[newR][newC].notifyObservers();
		if (whitesTurn) {
			player2->removePiece(attackedPiece->getId());
		} else {
			player1->removePiece(attackedPiece->getId());
		}
	}
	squares[newR][newC].setPiece(piece);
	// Update graphics
	undrawPiece(newR, newC);
	undrawPiece(curR, curC);
	drawPiece(piece);
	// Add piece to new square
	State nState{StateType::PieceAdded, Direction::N, true, piece, false};
	squares[newR][newC].setState(nState);
	squares[newR][newC].notifyObservers();
	// Progress game
	moves++;
	if (whitesTurn) {
		whitesTurn = false;
	} else {
		whitesTurn = true;
	}
}

Move Board::isLegalMove(shared_ptr<Piece> curPiece, int newR, int newC) {
	int curR = curPiece->getCoor().first;
	int curC = curPiece->getCoor().second;
	bool pieceOnSq = false;
	bool blocked = false;
	bool moveIntoAttack = false;
	bool checked = false;
	bool curWhite = curPiece->getIsWhite();
	Move move{pair<int, int>(newR, newC), curPiece};

	
	if (curR >= 0 && curR < 8 && curC >= 0 && curC < 8 && newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && !(curR == newR && curC == newC)) {

		// Check new square
		Info newInfo = squares[newR][newC].getInfo();
		if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
			moveIntoAttack = true;
		}
		if (newInfo.piece != nullptr) {
			if (newInfo.piece->getIsWhite() != curWhite) {	
				pieceOnSq = true;
				move.toCapture = true;
			} else {
				blocked = true;
			}				
		} else {
			move.toCapture = false;
		}

		// Check if move is avoiding capture
		Info curInfo = squares[curR][curC].getInfo();
		if (curWhite && curInfo.bAttacked && !moveIntoAttack) {
			move.toAvoid = true;
		} else if (!curWhite && curInfo.wAttacked && !moveIntoAttack) {
			move.toAvoid = true;
		} else {
			move.toAvoid = false;
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


		// Check if square is under attack (for king)
		newInfo = squares[curR][curC].getInfo();
		if ((curWhite && newInfo.bAttacked) || (!curWhite && newInfo.wAttacked)) {
			checked = true;
		}
		move.isLegal = false;
		
		// Move piece
		try {
			move.isLegal = curPiece->move(newR, newC, moves, pieceOnSq, blocked, moveIntoAttack, checked);
			curPiece->updatePiece(newR, newC);
			shared_ptr<Piece> castledRook = nullptr;
			// Castle
			if (curPiece->getCastle() == 1) {
				castledRook = squares[curR][curC + 3].getInfo().piece;
				if (castledRook->getMovesMade() == 0) {
					move.isLegal = true;
				}
			} else if (curPiece->getCastle() == 2) {
				castledRook = squares[curR][curC - 4].getInfo().piece;
				if (castledRook->getMovesMade() == 0) {
					move.isLegal = true;
				}
			} else {
				
				shared_ptr<Piece> capturedPiece = squares[newR][newC].getInfo().piece;
				
				updateTurn(curR, curC, newR, newC, curPiece);

				// Check if move will put opponent in check
				if (curWhite && player2->isInCheck()) {
					move.toCheck = true;
				} else if (!curWhite && player1->isInCheck()) {
					move.toCheck = true;
				} else {
					move.toCheck = false;
				}

				// Detect check
				if (whitesTurn) {
					if (!player2->isInCheck()) {
						move.isLegal = true;
					} else {
						move.isLegal = false;
					}
					curPiece->updatePiece(curR, curC);
					// Move pieces back
					updateTurn(newR, newC, curR, curC, curPiece);
					curPiece->decrementMoves(2);
					moves -= 2;
					if (capturedPiece != nullptr) {
						// Update twice to reset turn
						updateTurn(newR, newC, newR, newC, capturedPiece);
						updateTurn(newR, newC, newR, newC, capturedPiece);
						capturedPiece->decrementMoves(2);
						player1->addPiece(capturedPiece);
						moves -= 2;
					}
				} else {
					if (!player1->isInCheck()) {
						move.isLegal = true;
					} else {
						move.isLegal = false;
					}
					curPiece->updatePiece(curR, curC);
					// Move pieces back
					updateTurn(newR, newC, curR, curC, curPiece);
					curPiece->decrementMoves(2);
					moves -= 2;
					if (capturedPiece != nullptr) {
						// Update twice to reset turn
						updateTurn(newR, newC, newR, newC, capturedPiece);
						updateTurn(newR, newC, newR, newC, capturedPiece);
						capturedPiece->decrementMoves(2);
						player2->addPiece(capturedPiece);
						moves -= 2;
					}
				}
			}
		} catch (string msg) {
			return move;
		}
		return move;
	} else {
		move.isLegal = false;
		return move;
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
	drawBoard();
	drawSetupMenu();
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
			} else if (cmd == "clear") {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						defSquares[i][j].setPiece(nullptr);
					}
				}
				drawBoard();
				whiteCounts = {0, 0, 0, 0, 0, 0};
				blackCounts = {0, 0, 0, 0, 0, 0};
				drawSetupMenu();
				printDefault();
			} else if (cmd == "done") {
				setPlayer("white", "human");
				setPlayer("black", "human");
				init();
				if (whiteCounts[0] == 0 || blackCounts[0] == 0) {
					cout << "Both kings must be on the board." << endl;
				} else if (player1->isInCheck() || player2->isInCheck()) {
					cout << "Kings cannot be in check." << endl;	
				} else {
					done = true;
				}
			} else {
				cout << "Please enter a valid command." << endl;
				cin.clear();
				cin.ignore();
			}	
		} catch (string e) {
			cout << e << endl;
		} catch (...) { 
			cin.clear();
			cin.ignore();
		}
	} 
	window.fillRectangle(0, 0, 600, 60, 0);
}

ostream & operator<<(ostream &out, const Board &b) {
	out << endl;
	for (int i = 0; i < 8; ++i) {
		out << 8 - i << " ";
		for (int j = 0; j < 8; ++j) {
			
			
			Info info = b.squares[i][j].getInfo();
		/*	
			if (info.bTotAttacks > 0) {
				cout << info.bTotAttacks << " ";
			
			//else if (info.wAttacked || info.bAttacked) {
			//	cout << info.bTotAttacks;
			} else {
				cout << "  ";
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
	out << endl <<  "  abcdefgh" << endl << endl;
	return out;	
}
