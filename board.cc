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

Board::Board() {
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
		shared_ptr<Piece> pawnb = make_shared<Rook>(1, i, false, "p" + to_string(i+1), 0);
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
                shared_ptr<Piece> pawnw = make_shared<Rook>(6, i, true, "P" + to_string(i+1), 0);
                defSquares[6][i].setPiece(pawnw);
        }
	//cout << "survived constructor!" << endl;
}

void Board::init() {
	cout << "in init" << endl;
	whitesTurn = defWhitesTurn;
	//squares.clear();
	squares = defSquares;
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

void Board::incWhiteScore() {
	whiteScore++;
}

void Board::incBlackScore() {
	blackScore++;
}

bool Board::whiteTurn() {
	return whitesTurn;
}

int Board::colToInt(char c) {
	if (c == 'a') {
		return 0;
	} else if (c == 'b') {
		return 1;
	} else if (c == 'c') {
		return 2;
	} else if (c == 'd') {
		return 3;
	} else if (c == 'e') {
		return 4;
	} else if (c == 'f') {
		return 5;
	} else if (c == 'g') {
		return 6;
	} else if (c == 'h') {
		return 7;
	} else {
		return -1;
	}
}

void Board::printDefault() {
	for (int i = 0; i < 8; ++i) {
		cout << 8 - i << " ";
		for (int j = 0; j < 8; ++j) {
			shared_ptr<Piece> piece = (defSquares[i][j]).getPiece();
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
/*
void Board::setup() {
	cout << "in setup!!" << endl;
	init();
	cout << "survived init!!" << endl;
	cout << (*this);

	bool done = false;

	string cmd;
	while (!done) {
		try {
			cout << "made it!!" << endl;
			cin >> cmd;
			
			if (cmd == "+") {
				char piece;
				char col;
				int row;
				shared_ptr<Piece> p;
				cin >> piece >> col >> row;

				if (piece == 'K' && whiteCounts[0] == 0){
					p = make_shared<King>(8-row, colToInt(col), true, "K", 0);
					whiteCounts[0]++;
				} else if (piece == 'Q' && whiteCounts[0] == 0){
					p = make_shared<Queen>(8-row, colToInt(col), true, "Q", 0);
					whiteCounts[1]++;
				} else if (piece == 'B' && whiteCounts[2] < 2){
					p = make_shared<Bishop>(8-row, colToInt(col), true, "B" + to_string(whiteCounts[2]), 0);
					whiteCounts[2]++;
				} else if (piece == 'R' && whiteCounts[3] < 2){
					p = make_shared<Rook>(8-row, colToInt(col), true, "R" + to_string(whiteCounts[3]), 0);
					whiteCounts[3]++;
				} else if (piece == 'N' && whiteCounts[4] < 2){
					p = make_shared<Knight>(8-row, colToInt(col), true, "N" + to_string(whiteCounts[4]), 0);
					whiteCounts[4]++;
				} else if (piece == 'P' && whiteCounts[5] < 8){
					if (row == 1 || row == 8) {
						throw InvalidPawn();
					}
					p = make_shared<Pawn>(8-row, colToInt(col), true, "P" + to_string(whiteCounts[5]), 0);
					whiteCounts[5]++;
				} else if (piece == 'k' && blackCounts[0] == 0){
					p = make_shared<King>(8-row, colToInt(col), false, "k", 0);
					blackCounts[0]++;
				} else if (piece == 'q' && blackCounts[1] == 0){
					p = make_shared<Queen>(8-row, colToInt(col), false, "q", 0);
					blackCounts[1]++;
				} else if (piece == 'b' && blackCounts[0] == 0){
					p = make_shared<Bishop>(8-row, colToInt(col), false, "b" + to_string(blackCounts[2]), 0);
					blackCounts[2]++;
				} else if (piece == 'r' && blackCounts[0] == 0){
					p = make_shared<Rook>(8-row, colToInt(col), false, "r" + to_string(blackCounts[3]), 0);
					blackCounts[3]++;
				} else if (piece == 'n' && blackCounts[0] == 0){
					p = make_shared<Knight>(8-row, colToInt(col), false, "n" + to_string(blackCounts[4]), 0);
					blackCounts[4]++;
				} else if (piece == 'p' && blackCounts[0] == 0){
					if (row == 1 || row == 8) {
						throw InvalidPawn();
					}
					p = make_shared<Pawn>(8-row, colToInt(col), false, "p" + to_string(blackCounts[5]), 0);
					blackCounts[5]++;
				} else { // either input error or pieces of that type are already on the board
					throw InvalidInput();
				}
				defSquares[8-row][colToInt(col)].setPiece(p);
				printDefault();

			} else if (cmd == "-") {
				// have to delete unused pieces?
				
				char col;
				int row;	
				cin >> col >> row;
				shared_ptr<Piece> p = squares[8-row][colToInt(col)].getPiece();
				if (p) {

					string id = p->getId();
					char piece = id.at(0);

					switch(piece) {
						case 'K': whiteCounts[0]--;
						case 'Q': whiteCounts[1]--;
						case 'B': whiteCounts[2]--;
						case 'R': whiteCounts[3]--;
						case 'N': whiteCounts[4]--;
						case 'P': whiteCounts[5]--;
						case 'k': blackCounts[0]--;
						case 'q': blackCounts[1]--;
						case 'b': blackCounts[2]--;
						case 'r': blackCounts[3]--;
						case 'n': blackCounts[4]--;
						case 'p': blackCounts[5]--;
						default: break;
					}

					defSquares[8-row][colToInt(col)].setPiece(nullptr);
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
					throw InvalidInput();
				}
			} else if (cmd == "done") {
				if (whiteCounts[0] == 0 || blackCounts[0] == 0) {
					cout << "Both kings must be on the board." << endl;
				// add checks to make sure neither player is in check	
				} else {
					done = true;
				}
			}	
		} catch (InvalidInput) {
			cout << "Invalid input" << endl;
		} catch (InvalidPawn) {
			cout << "You cannot place pawns on the first or last row of the board." << endl;	
		} catch(...) {}
	} 
}
*/
void Board::setup() {
	printDefault();
	bool done = false;
	string cmd;
	while (!done) {
		try{
			cin >> cmd;
			
			if (cmd == "+") {
				char piece;
				char col;
				int row;
				shared_ptr<Piece> p;
				cin >> piece >> col >> row;

				if (piece == 'K' && whiteCounts[0] == 0){
					p = make_shared<King>(8-row, colToInt(col), true, "K", 0);
					whiteCounts[0]++;
				} else if (piece == 'Q' && whiteCounts[1] == 0){
					p = make_shared<Queen>(8-row, colToInt(col), true, "Q", 0);
					whiteCounts[1]++;
				} else if (piece == 'B' && whiteCounts[2] < 2){
					p = make_shared<Bishop>(8-row, colToInt(col), true, "B" + to_string(whiteCounts[2]), 0);
					whiteCounts[2]++;
				} else if (piece == 'R' && whiteCounts[3] < 2){
					p = make_shared<Rook>(8-row, colToInt(col), true, "R" + to_string(whiteCounts[3]), 0);
					whiteCounts[3]++;
				} else if (piece == 'N' && whiteCounts[4] < 2){
					p = make_shared<Knight>(8-row, colToInt(col), true, "N" + to_string(whiteCounts[4]), 0);
					whiteCounts[4]++;
				} else if (piece == 'P' && whiteCounts[5] < 8){
					if (row == 1 || row == 8) {
						throw InvalidPawn();
					}
					p = make_shared<Pawn>(8-row, colToInt(col), true, "P" + to_string(whiteCounts[5]), 0);
					whiteCounts[5]++;
				} else if (piece == 'k' && blackCounts[0] == 0){
					p = make_shared<King>(8-row, colToInt(col), false, "k", 0);
					blackCounts[0]++;
				} else if (piece == 'q' && blackCounts[1] == 0){
					p = make_shared<Queen>(8-row, colToInt(col), false, "q", 0);
					blackCounts[1]++;
				} else if (piece == 'b' && blackCounts[2] < 2){
					p = make_shared<Bishop>(8-row, colToInt(col), false, "b" + to_string(blackCounts[2]), 0);
					blackCounts[2]++;
				} else if (piece == 'r' && blackCounts[3] < 2){
					p = make_shared<Rook>(8-row, colToInt(col), false, "r" + to_string(blackCounts[3]), 0);
					blackCounts[3]++;
				} else if (piece == 'n' && blackCounts[4] < 2){
					p = make_shared<Knight>(8-row, colToInt(col), false, "n" + to_string(blackCounts[4]), 0);
					blackCounts[4]++;
				} else if (piece == 'p' && blackCounts[5] < 8){
					if (row == 1 || row == 8) {
						throw InvalidPawn();
					}
					p = make_shared<Pawn>(8-row, colToInt(col), false, "p" + to_string(blackCounts[5]), 0);
					blackCounts[5]++;
				} else { // either input error or pieces of that type are already on the board
					throw InvalidInput();
				}
				defSquares[8-row][colToInt(col)].setPiece(p);
				printDefault();

			} else if (cmd == "-") {
				// have to delete unused pieces?
				
				char col;
				int row;	
				cin >> col >> row;
				shared_ptr<Piece> p = defSquares[8-row][colToInt(col)].getPiece();
				if (p) {

					string id = p->getId();
					char piece = id.at(0);

					switch(piece) {
						case 'K': whiteCounts[0]--;
						case 'Q': whiteCounts[1]--;
						case 'B': whiteCounts[2]--;
						case 'R': whiteCounts[3]--;
						case 'N': whiteCounts[4]--;
						case 'P': whiteCounts[5]--;
						case 'k': blackCounts[0]--;
						case 'q': blackCounts[1]--;
						case 'b': blackCounts[2]--;
						case 'r': blackCounts[3]--;
						case 'n': blackCounts[4]--;
						case 'p': blackCounts[5]--;
						default: break;
					}

					defSquares[8-row][colToInt(col)].setPiece(nullptr);
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
					throw InvalidInput();
				}
			} else if (cmd == "done") {
				if (whiteCounts[0] == 0 || blackCounts[0] == 0) {
					cout << "Both kings must be on the board." << endl;
				// add checks to make sure neither player is in check	
				} else {
					done = true;
				}
			}	
		} catch(InvalidInput &e){
			cout << "Invalid." << endl;
		} catch(InvalidPawn &e){
			cout << "You cannot place a pawn on the first or last row." << endl;	
		} catch (...) {}
	} 
}

