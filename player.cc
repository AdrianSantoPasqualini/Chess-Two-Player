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

int Player::howManyLegalMoves() {
	return legalMoves.size();
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
		Move move;
		if (id[0] == 'R' || id[0] == 'r') {
			for (int i = 1; i < 8; i ++) {
				move = board->isLegalMove(piece, curR + i, curC);
				bool legalUp = move.isLegal;
				if (legalUp) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR - i, curC);
				bool legalDown = move.isLegal;
				if (legalDown) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR, curC - i);
				bool legalLeft = move.isLegal;
				if (legalLeft) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curC, curC + i);
				bool legalRight = move.isLegal;
				if (legalRight) {
					legalMoves.emplace_back(move);
				}
			}
		} else if (id[0] == 'B' || id[0] == 'b') {
			for (int i = 1; i < 8; i ++) {
				move = board->isLegalMove(piece, curR + i, curC + i);
				bool legalNE = move.isLegal;
				if (legalNE) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR + i, curC - i);
				bool legalNW = move.isLegal;
				if (legalNW) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR - i, curC - i);
				bool legalSW = move.isLegal;
				if (legalSW) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR - i, curC + i);
				bool legalSE = board.isLegal;
				if (legalSE) {
					legalMoves.emplace_back(move);
				}
			}
		} else if (id[0] == 'P') {
			move = board->isLegalMove(piece, curR - 1, curC - 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			} 
			move = board->isLegalMove(piece, curR - 1, curC);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
			move = board->isLegalMove(piece, curR - 1, curC + 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
		} else if (id[0] == 'p') {
			move = board->isLegalMove(piece, curR + 1, curC - 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			} 
			move = board->isLegalMove(piece, curR + 1, curC);
			if (move.isLegal) {
				legalMoves.emplace_back(move);

			}
			move = board->isLegalMove(piece, curR + 1, curC + 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
		} else if (id[0] == 'K' || id[0] == 'k') {
			for (int h = -1; h <= 1; h++) {
				for (int w = -1; w <= 1; w++) {
					if ((w != 0) || (h != 0)) {
						move = board->isLegalMove(piece, curR + h, curC + w);
						if (move.isLegal) {
							legalMoves.emplace_back(move);
						}
					}
				}
			}
		} else if (id[0] == 'N' || id[0] == 'n') {
			move = board->isLegalMove(piece, curR + 1, curC + 2);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			} 
			move = board->isLegalMove(piece, curR + 1, curC - 2);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
			move = board->isLegalMove(piece, curR - 1, curC + 2);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
			move = board->isLegalMove(piece, curR - 1, curC - 2);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			} 
			move = board->isLegalMove(piece, curR + 2, curC + 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);

			}
			move = board->isLegalMove(piece, curR + 2, curC - 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
			move = board->isLegalMove(piece, curR - 2, curC + 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			} 
			move = board->isLegalMove(piece, curR - 2, curC - 1);
			if (move.isLegal) {
				legalMoves.emplace_back(move);
			}
		} else {
			for (int i = 1; i < 8; i++) {
				move = board->isLegalMove(piece, curR + i, curC);
				bool legalUp = move.isLegal;
				if (legalUp) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR - i, curC);
				bool legalDown = move.isLegal;
				if (legalDown) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR, curC - i);
				bool legalLeft = move.isLegal;
				if (legalLeft) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR, curC + i);
				bool legalRight = move.isLegal;
				if (legalRight) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR + i, curC + i);
				bool legalNE = move.isLegal;
				if (legalNE) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR + i, curC - i);
				bool legalNW = move.isLegal;
				if (legalNW) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR - i, curC - i);
				bool legalSW = move.isLegal;
				if (legalSW) {
					legalMoves.emplace_back(move);
				}
				move = board->isLegalMove(piece, curR - i, curC + i);
				bool legalSE = move.isLegal;
				if (legalSE) {
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
//	generateLegalMoves();
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
