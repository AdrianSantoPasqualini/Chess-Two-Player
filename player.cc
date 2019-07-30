#include "player.h"
#include "piece.h"
#include "board.h"
#include "info.h"
#include <ctime>    
#include <cstdlib>

using namespace std;

///////////////////////// HOW TO RANDOM ////////////////////////////
// srand(time(0)); // Sets the random seed based on the current time.
// r = (rand() % x); // Generates random number from 0 to x.
////////////////////////////////////////////////////////////////////

Player::Player(bool isWhite): isWhite {isWhite} {
	score = 0;	
	legalMoves = {};
}

bool Player::isInCheck() const {
	bool check = false;
	pair<int, int> coor;
	if (isWhite) {
		coor = pieces.find("K")->second->getCoor();
		int bAttacks = board->getAttacks(coor.first, coor.second).second;
		if (bAttacks) {
			check = true;
		}
	} else {
		coor = pieces.find("k")->second->getCoor();
		int wAttacks = board->getAttacks(coor.first, coor.second).first;
		if (wAttacks) {
			check = true;
		}
	}
	return check;
}

void Player::attachBoard(Board * currBoard) {
	board = currBoard;
}

void Player::addPiece(shared_ptr<Piece> p) {
	pieces.emplace(p->getId(), p);
}

void Player::removePiece(string id) {
	pieces.erase(id);
}



void Player::generateLegalMoves() {
	legalMoves.clear();
	map<string, shared_ptr<Piece>>::iterator it = pieces.begin();
	while(it != pieces.end()) {
		string id = it->first;
		shared_ptr<Piece> piece = it->second;
		int curR = piece->getCoor().first;
		int curC = piece->getCoor().second;
		if (id[0] == 'R' || id[0] == 'r') {
			for (int i = 1; i < 8; i ++) {
				bool legalUp = board->isLegalMove(piece, curR + i, curC);
				bool legalDown = board->isLegalMove(piece, curR - i, curC);
				bool legalLeft = board->isLegalMove(piece, curR, curC - i);
				bool legalRight = board->isLegalMove(piece, curR, curC + i);
				if (legalUp) {
					Move move{make_pair(curR + i, curC), piece};
					legalMoves.emplace_back(move);
				}
				if (legalDown) {
					Move move{make_pair(curR - i, curC), piece};
					legalMoves.emplace_back(move);
				}
				if (legalLeft) {
					Move move{make_pair(curR, curC - i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalRight) {
					Move move{make_pair(curR, curC + i), piece};
					legalMoves.emplace_back(move);
				}
			}
		} else if (id[0] == 'B' || id[0] == 'b') {
			for (int i = 1; i < 8; i ++) {
				bool legalNE = board->isLegalMove(piece, curR + i, curC + i);
				bool legalNW = board->isLegalMove(piece, curR + i, curC - i);
				bool legalSW = board->isLegalMove(piece, curR - i, curC - i);
				bool legalSE = board->isLegalMove(piece, curR - i, curC + i);
				if (legalNE) {
					Move move{make_pair(curR + i, curC + i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalNW) {
					Move move{make_pair(curR + i, curC - i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalSW) {
					Move move{make_pair(curR - i, curC - i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalSE) {
					Move move{make_pair(curR - i, curC + i), piece};
					legalMoves.emplace_back(move);
				}
			}
		} else if (id[0] == 'P') {
			if (board->isLegalMove(piece, curR - 1, curC - 1)) {
				Move move{make_pair(curR - 1, curC - 1), piece};
				legalMoves.emplace_back(move);
			} 
			if (board->isLegalMove(piece, curR - 1, curC)) {
				Move move{make_pair(curR - 1, curC), piece};
				legalMoves.emplace_back(move);

			}
			if (board->isLegalMove(piece, curR - 1, curC + 1)) {
				Move move{make_pair(curR - 1, curC + 1), piece};
				legalMoves.emplace_back(move);
			}
		} else if (id[0] == 'p') {
			if (board->isLegalMove(piece, curR + 1, curC - 1)) {
				Move move{make_pair(curR + 1, curC - 1), piece};
				legalMoves.emplace_back(move);
			} 
			if (board->isLegalMove(piece, curR + 1, curC)) {
				Move move{make_pair(curR + 1, curC), piece};
				legalMoves.emplace_back(move);

			}
			if (board->isLegalMove(piece, curR + 1, curC + 1)) {
				Move move{make_pair(curR + 1, curC + 1), piece};
				legalMoves.emplace_back(move);
			}
		} else if (id[0] == 'K' || id[0] == 'k') {
			for (int h = -1; h <= 1; h++) {
				for (int w = -1; w <= 1; w++) {
					if (((w != 0) || (h != 0)) && board->isLegalMove(piece, curR + h, curC + w)) {
						Move move{make_pair(curR + h, curC + w), piece};
						legalMoves.emplace_back(move);
					}
				}
			}
		} else if (id[0] == 'N' || id[0] == 'n') {
			if (board->isLegalMove(piece, curR + 1, curC + 2)) {
				Move move{make_pair(curR + 1, curC + 2), piece};
				legalMoves.emplace_back(move);
			} 
			if (board->isLegalMove(piece, curR + 1, curC - 2)) {
				Move move{make_pair(curR + 1, curC - 2), piece};
				legalMoves.emplace_back(move);

			}
			if (board->isLegalMove(piece, curR - 1, curC + 2)) {
				Move move{make_pair(curR - 1, curC + 2), piece};
				legalMoves.emplace_back(move);
			}
			if (board->isLegalMove(piece, curR - 1, curC - 2)) {
				Move move{make_pair(curR - 1, curC - 2), piece};
				legalMoves.emplace_back(move);
			} 
			if (board->isLegalMove(piece, curR + 2, curC + 1)) {
				Move move{make_pair(curR + 2, curC + 1), piece};
				legalMoves.emplace_back(move);

			}
			if (board->isLegalMove(piece, curR + 2, curC - 1)) {
				Move move{make_pair(curR + 2, curC - 1), piece};
				legalMoves.emplace_back(move);
			}
			if (board->isLegalMove(piece, curR - 2, curC + 1)) {
				Move move{make_pair(curR - 2, curC + 1), piece};
				legalMoves.emplace_back(move);
			} 
			if (board->isLegalMove(piece, curR - 2, curC - 1)) {
				Move move{make_pair(curR - 2, curC - 1), piece};
				legalMoves.emplace_back(move);
			}
		} else {
			for (int i = 1; i < 8; i++) {
				bool legalUp = board->isLegalMove(piece, curR + i, curC);
				bool legalDown = board->isLegalMove(piece, curR - i, curC);
				bool legalLeft = board->isLegalMove(piece, curR, curC - i);
				bool legalRight = board->isLegalMove(piece, curR, curC + i);
				bool legalNE = board->isLegalMove(piece, curR + i, curC + i);
				bool legalNW = board->isLegalMove(piece, curR + i, curC - i);
				bool legalSW = board->isLegalMove(piece, curR - i, curC - i);
				bool legalSE = board->isLegalMove(piece, curR - i, curC + i);
				if (legalUp) {
					Move move{make_pair(curR + i, curC), piece};
					legalMoves.emplace_back(move);
				}
				if (legalDown) {
					Move move{make_pair(curR - i, curC), piece};
					legalMoves.emplace_back(move);
				}
				if (legalLeft) {
					Move move{make_pair(curR, curC - i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalRight) {
					Move move{make_pair(curR, curC + i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalNE) {
					Move move{make_pair(curR + i, curC + i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalNW) {
					Move move{make_pair(curR + i, curC - i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalSW) {
					Move move{make_pair(curR - i, curC - i), piece};
					legalMoves.emplace_back(move);
				}
				if (legalSE) {
					Move move{make_pair(curR - i, curC + i), piece};
					legalMoves.emplace_back(move);
				}
			}
		}
		it++;
	}
}



Human::Human(bool isWhite): Player{isWhite} {}

void Human::makeMove() {
	string oldCoord;
	string newCoord;
	cin >> oldCoord >> newCoord;
	board->movePiece('8' - oldCoord[1], oldCoord[0] - 'a', '8' - newCoord[1], newCoord[0] - 'a');
}

Level1::Level1(bool isWhite): Player{isWhite} {}

void Level1::makeMove() {
	generateLegalMoves();
	srand(time(NULL));	
	int r = rand() % legalMoves.size();
	pair<int, int> oldCoords = legalMoves[r].piece->getCoor();
	pair<int, int> newCoords = legalMoves[r].nCoords;
	board->movePiece(oldCoords.first, oldCoords.second, newCoords.first, newCoords.second);
}

Level2::Level2(bool isWhite): Player{isWhite} {}

void Level2::makeMove() {
	generateLegalMoves();
	int prefMoves = 0;
	srand(time(NULL));	
	for (unsigned int i = 0; i < legalMoves.size(); i++) {
		if (legalMoves[i].toCapture || legalMoves[i].toCheck) {
			prefMoves++;
		}
	}
	if (prefMoves == 0) {
		int r = rand() % legalMoves.size();
		pair<int, int> oldCoords = legalMoves[r].piece->getCoor();
		pair<int, int> newCoords = legalMoves[r].nCoords;
		board->movePiece(oldCoords.first, oldCoords.second, newCoords.first, newCoords.second);

	} else {
		int r = rand() % prefMoves;
		for (unsigned int i = 0; i < legalMoves.size(); i++) {
			if (legalMoves[i].toCapture || legalMoves[i].toCheck) {
				if (r == 0) {
					pair<int, int> oldCoords = legalMoves[i].piece->getCoor();
					pair<int, int> newCoords = legalMoves[i].nCoords;
					board->movePiece(oldCoords.first, oldCoords.second, newCoords.first, newCoords.second);
					return;
				} 
				r--;
			}
		}
	}
}

Level3::Level3(bool isWhite): Player{isWhite} {}

void Level3::makeMove() {
	generateLegalMoves();
	int prefMoves = 0;
	srand(time(NULL));	
	for (unsigned int i = 0; i < legalMoves.size(); i++) {
		if (legalMoves[i].toAvoid || legalMoves[i].toCapture || legalMoves[i].toCheck) {
			prefMoves++;
		}
	}
	if (prefMoves == 0) {
		int r = rand() % legalMoves.size();
		pair<int, int> oldCoords = legalMoves[r].piece->getCoor();
		pair<int, int> newCoords = legalMoves[r].nCoords;
		board->movePiece(oldCoords.first, oldCoords.second, newCoords.first, newCoords.second);

	} else {
		int r = rand() % prefMoves;
		for (unsigned int i = 0; i < legalMoves.size(); i++) {
			if (legalMoves[i].toAvoid || legalMoves[i].toCapture || legalMoves[i].toCheck) {
				if (r == 0) {
					pair<int, int> oldCoords = legalMoves[i].piece->getCoor();
					pair<int, int> newCoords = legalMoves[i].nCoords;
					board->movePiece(oldCoords.first, oldCoords.second, newCoords.first, newCoords.second);
					return;
				} 
				r--;
			}
		}
	}
}

Level4::Level4(bool isWhite): Player{isWhite} {}

void Level4::makeMove() {

}
