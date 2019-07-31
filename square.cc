#include "square.h"
#include "piece.h"
#include "info.h"
#include <iostream>
using namespace std;

Square::Square(int r, int c, shared_ptr<Piece> currPiece): currPiece{currPiece}, r{r}, c{c} {}


Square::Square(const Square & other): r{other.r}, c{other.c}  {
	shared_ptr<Piece> piece = other.getInfo().piece;
	if (piece == nullptr) {
		currPiece = nullptr;	
	} else {
		char id = toupper(piece->getId().at(0));
		if (id == 'K') {
			currPiece = make_shared<King>(r, c, piece->getIsWhite(), piece->getId());
		} else if (id == 'Q') {
			currPiece = make_shared<Queen>(r, c, piece->getIsWhite(), piece->getId());
		} else if (id == 'B') {
			currPiece = make_shared<Bishop>(r, c, piece->getIsWhite(), piece->getId());
		} else if (id == 'R') {
			currPiece = make_shared<Rook>(r, c, piece->getIsWhite(), piece->getId());
		} else if (id == 'N') {
			currPiece = make_shared<Knight>(r, c, piece->getIsWhite(), piece->getId());
		} else if (id == 'P') {
			currPiece = make_shared<Pawn>(r, c, piece->getIsWhite(), piece->getId());
		}
	}
}


void Square::setPiece(shared_ptr<Piece> piece) {
	currPiece = piece;
}


Info Square::getInfo() const {
	pair<int, int> coords{r, c};
	int wTotAttacks = wAttacks.size();
	int bTotAttacks = bAttacks.size();
	Info nInfo{coords, currPiece, wAttacks.size() != 0, bAttacks.size() != 0, wTotAttacks, bTotAttacks};
	return nInfo;
}


void Square::removeAttacker(bool white, string id) {
	if (white) {
		for (unsigned int i = 0; i < wAttacks.size(); i++) {
			if (wAttacks[i]->getId() == id) {
				wAttacks.erase(wAttacks.begin() + i);
				break;
			}
		}
	} else {
		for (unsigned int i = 0; i < bAttacks.size(); i++) {
			if (bAttacks[i]->getId() == id) {
				bAttacks.erase(bAttacks.begin() + i);
				break;
			}
		}
	}
}


void Square::addAttacker(bool white, shared_ptr<Piece> piece) {
	if (white) {
		bool found = false;
		for (unsigned int i = 0; i < wAttacks.size(); i++) {
			if (piece->getId() == wAttacks[i]->getId()) {
				found = true;
				break;
			}
		}
		if (!found) {
			wAttacks.emplace_back(piece);
		}
	} else {	
		bool found = false;
		for (unsigned int i = 0; i < bAttacks.size(); i++) {
			if (piece->getId() == bAttacks[i]->getId()) {
				found = true;
				break;
			}
		}
		if (!found) {
			bAttacks.emplace_back(piece);
		}
	}
}


void Square::toggleAttacker(bool attacked, shared_ptr<Piece> piece) {
	if (attacked) {
		addAttacker(piece->getIsWhite(), piece);
	} else {
		removeAttacker(piece->getIsWhite(), piece->getId());
	}
}


void Square::notify(Subject & whoFrom) {
	State recState = whoFrom.getState();
	pair<int,int> recCoords = whoFrom.getInfo().coords;
	State currState = getState();
	pair<int,int> currCoords = getInfo().coords;
	int currRow = currCoords.first;
	int currCol = currCoords.second;
	int recRow = recCoords.first;
	int recCol = recCoords.second;
	Direction direction;
	Direction revDir;
	if ((currCol == recCol) && (currRow < recRow)) {
		direction = Direction::N;
		revDir = Direction::S;
	} else if ((currCol == recCol) && (currRow > recRow)) {
		direction = Direction::S;
		revDir = Direction::N;
	} else if ((currRow == recRow) && (currCol < recCol)) {
		direction = Direction::W;
		revDir = Direction::E;
	} else if ((currRow == recRow) && (currCol > recCol)) {
		direction = Direction::E;
		revDir = Direction::W;
	} else if ((currCol < recCol) && (currRow < recRow)) {
		direction = Direction::NW;
		revDir = Direction::SE;
	} else if ((currCol < recCol) && (currRow > recRow)) {
		direction = Direction::SW;
		revDir = Direction::NE;
	} else if ((currCol > recCol) && (currRow < recRow)) {
		direction = Direction::NE;
		revDir = Direction::SW;
	} else {
		direction = Direction::SE;
		revDir = Direction::NW;
	}
	bool vertical = (direction == Direction::N || direction == Direction::S);
	bool horizontal = (direction == Direction::E || direction == Direction::W);
	bool downDiagonal = (direction == Direction::NW || direction == Direction::SE);
	bool upDiagonal = (direction == Direction::NE || direction == Direction::SW);
	bool pawnAttacked;
	if (recState.piece->getIsWhite()) {
		pawnAttacked = (direction == Direction::NW || direction == Direction::NE);
	} else {
		pawnAttacked = (direction == Direction::SE || direction == Direction::SW);
	}
	if (recState.type == StateType::PieceAdded) {
		if (getInfo().piece == nullptr) {
			if (recState.piece->getId()[0] == 'r' || recState.piece->getId()[0] == 'R') {
				if (vertical || horizontal) {
					State nState{StateType::Relay, direction, true, recState.piece, false};
					setState(nState);
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				} else {
					State nState{StateType::Relay, direction, false, recState.piece, false};
					setState(nState);
				}
				notifyObservers();
			} else if (recState.piece->getId()[0] == 'b' || recState.piece->getId()[0] == 'B') {
				if (downDiagonal || upDiagonal) {
					State nState{StateType::Relay, direction, true, recState.piece, false};
					setState(nState);
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				} else {
					State nState{StateType::Relay, direction, false, recState.piece, false};
					setState(nState);
				}
				notifyObservers();
			} else if (recState.piece->getId()[0] == 'p' || recState.piece->getId()[0] == 'P') {
				if (pawnAttacked) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				}	
				State nState{StateType::Relay, direction, false, recState.piece, false};
				setState(nState);
				notifyObservers();
			} else if (recState.piece->getId()[0] == 'k' || recState.piece->getId()[0] == 'K') {
				addAttacker(recState.piece->getIsWhite(), recState.piece);
				State nState{StateType::Relay, direction, false, recState.piece, false};
				setState(nState);
				notifyObservers();
			} else if (recState.piece->getId()[0] == 'n' || recState.piece->getId()[0] == 'N') {
				if (vertical || horizontal) {
					State nState{StateType::Relay, direction, true, recState.piece, true};
					setState(nState);
					notifyObservers();
				}
				State nState{StateType::Relay, direction, false, recState.piece, false};
				setState(nState);
				notifyObservers();
			} else {
				State nState{StateType::Relay, direction, true, recState.piece, false};
				setState(nState);
				addAttacker(recState.piece->getIsWhite(), recState.piece);
				notifyObservers();
			}
		} else {
			if (recState.piece->getId()[0] == 'r' || recState.piece->getId()[0] == 'R') {
				if (vertical || horizontal) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				}
			} else if (recState.piece->getId()[0] == 'b' || recState.piece->getId()[0] == 'B') {
				if (downDiagonal || upDiagonal) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				}
			} else if (recState.piece->getId()[0] == 'p' || recState.piece->getId()[0] == 'P') {
				if (pawnAttacked) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				}
			} else if (recState.piece->getId()[0] == 'n' || recState.piece->getId()[0] == 'N') {
				if (vertical || horizontal) {
					State nState{StateType::Relay, direction, true, recState.piece, true};
					setState(nState);
					notifyObservers();
				}
			} else {
				//King and Queen
				addAttacker(recState.piece->getIsWhite(), recState.piece);
			}
			if (getInfo().piece->getId()[0] == 'r' || getInfo().piece->getId()[0] == 'R') {
				if (vertical || horizontal) {
					State nState{StateType::Reply, revDir, true, getInfo().piece, false};
					setState(nState);
					notifyObservers();
				}
			} else if (getInfo().piece->getId()[0] == 'b' || getInfo().piece->getId()[0] == 'B') {
				if (downDiagonal || upDiagonal) {
					State nState{StateType::Reply, revDir, true, getInfo().piece, false};
					setState(nState);
					notifyObservers();
				}
			} else if (getInfo().piece->getId()[0] == 'p' || getInfo().piece->getId()[0] == 'P'){
				//Pawns do not send replies.
			} else if (getInfo().piece->getId()[0] == 'k' || getInfo().piece->getId()[0] == 'K') {
				//Kings do not send replies.
			} else if (getInfo().piece->getId()[0] == 'n' || getInfo().piece->getId()[0] == 'N') {
				//Knights do not send replies.
			} else {
				State nState{StateType::Reply, revDir, true, getInfo().piece, false};
				setState(nState);
				notifyObservers();
			}
		}
	} else if (recState.type == StateType::PieceRemoved) {
		if (recState.piece->getId()[0] == 'n' || recState.piece->getId()[0] == 'N') {
			State nState{StateType::Relay, direction, false, recState.piece, true};
			setState(nState);
			notifyObservers();
		}
		if (getInfo().piece == nullptr) {
			State nState{StateType::Relay, direction, false, recState.piece, false};
			setState(nState);
			notifyObservers();
		} else {	
			if (getInfo().piece->getId()[0] == 'r' || getInfo().piece->getId()[0] == 'R') {
				if (vertical || horizontal) {
					State nState{StateType::Reply, revDir, true, getInfo().piece, false};
					setState(nState);
					notifyObservers();
				}
			} else if (getInfo().piece->getId()[0] == 'b' || getInfo().piece->getId()[0] == 'B') {
				if (downDiagonal || upDiagonal) {
					State nState{StateType::Reply, revDir, true, getInfo().piece, false};
					setState(nState);
					notifyObservers();
				}
			} else if (getInfo().piece->getId()[0] == 'p' || getInfo().piece->getId()[0] == 'P'){
				//Pawns do not send replies.
			} else if (getInfo().piece->getId()[0] == 'k' || getInfo().piece->getId()[0] == 'K') {
				//Kings do not send replies.
			} else if (getInfo().piece->getId()[0] == 'n' || getInfo().piece->getId()[0] == 'N') {
				//Knights do not send replies.
			} else {
				State nState{StateType::Reply, revDir, true, getInfo().piece, false};
				setState(nState);
				notifyObservers();
			}
		}
		removeAttacker(recState.piece->getIsWhite(), recState.piece->getId());
	} else if (recState.type == StateType::Relay) {
		if (direction == recState.direction) {
			if ((recState.piece->getId()[0] == 'n' || recState.piece->getId()[0] == 'N') && recState.knightMovement) {
				if (vertical) {
					State rState{StateType::Reply, Direction::E, recState.attacked, recState.piece, true};
					setState(rState);
					notifyObservers();
					State lState{StateType::Reply, Direction::W, recState.attacked, recState.piece, true};
					setState(lState);
					notifyObservers();
				} else if (horizontal) {
					State rState{StateType::Reply, Direction::N, recState.attacked, recState.piece, true};
					setState(rState);
					notifyObservers();
					State lState{StateType::Reply, Direction::S, recState.attacked, recState.piece, true};
					setState(lState);
					notifyObservers();
				}
			} else {
				if (getInfo().piece == nullptr) {
					State nState{StateType::Relay, direction, recState.attacked, recState.piece, false};
					setState(nState);
					toggleAttacker(recState.attacked, recState.piece);
					notifyObservers();
				} else if (getInfo().piece != nullptr) {
					toggleAttacker(recState.attacked, recState.piece);
					if (getInfo().piece->getId()[0] == 'r' || getInfo().piece->getId()[0] == 'R') {
						if (vertical || horizontal) {
							State nState{StateType::Reply, revDir, true, getInfo().piece, false};
							setState(nState);
							notifyObservers();
						}
					} else if  (getInfo().piece->getId()[0] == 'b' || getInfo().piece->getId()[0] == 'B') {
						if (downDiagonal || upDiagonal) {
							State nState{StateType::Reply, revDir, true, getInfo().piece, false};
							setState(nState);
							notifyObservers();
						}
					} else if (getInfo().piece->getId()[0] == 'p' || getInfo().piece->getId()[0] == 'P') {
						//Pawns do not send replies.
					} else if (getInfo().piece->getId()[0] == 'k' || getInfo().piece->getId()[0] == 'K') {
						//Kings do not send replies.
					} else if (getInfo().piece->getId()[0] == 'n' || getInfo().piece->getId()[0] == 'N') {
						//Knights do not send replies.
					} else {
						State nState{StateType::Reply, revDir, true, getInfo().piece, false};
						setState(nState);
						notifyObservers();
					}
				}
			}
		}
	} else if (recState.type == StateType::Reply) {
		if (direction == recState.direction) {
			if ((recState.piece->getId()[0] == 'n' || recState.piece->getId()[0] == 'N') && recState.knightMovement) {
				toggleAttacker(recState.attacked, recState.piece);
			} else {
				if (getInfo().piece == nullptr) {
					State nState{StateType::Reply, direction, recState.attacked, recState.piece, false};
					setState(nState);
					toggleAttacker(recState.attacked, recState.piece);
					notifyObservers();
				} else if (getInfo().piece != nullptr && recState.attacked) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
					State nState{StateType::Reply, direction, false, recState.piece, false};
					setState(nState);
					notifyObservers();
				} else {
					removeAttacker(recState.piece->getIsWhite(), recState.piece->getId());
				}
			}
		}
	}
	setState(currState);
}
