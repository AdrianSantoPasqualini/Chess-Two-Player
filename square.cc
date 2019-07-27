#include "square.h"
#include "piece.h"
#include "info.h"
#include <iostream>
using namespace std;


Square::Square(int r, int c, shared_ptr<Piece> currPiece): currPiece{currPiece}, r{r}, c{c} {}

shared_ptr<Piece> Square::getPiece() const {
	return currPiece;
}

void Square::setPiece(shared_ptr<Piece> piece) {
	currPiece = piece;
}

pair<int,int> Square::getCoords() const {
	return make_pair(r, c);
}

Info Square::getInfo() const {
	pair<int, int> coords{r, c};
	Info nInfo{coords, currPiece, wAttacks.size() != 0, bAttacks.size() != 0};
	return nInfo;
}


void Square::removeAttacker(bool white, string id) {
	if (white) {
		for (int i = 0; i < wAttacks.size(); i++) {
			if (wAttacks[i]->getId() == id) {
				wAttacks.erase(wAttacks.begin() + i);
			}
			break;
		}
	} else {
		for (int i = 0; i < bAttacks.size(); i++) {
			if (bAttacks[i]->getId() == id) {
				bAttacks.erase(bAttacks.begin() + i);
			}
			break;
		}
	}
}


void Square::addAttacker(bool white, shared_ptr<Piece> piece) {
	if (white) {
		wAttacks.emplace_back(piece);
	} else {
		bAttacks.emplace_back(piece);
	}
}



void Square::notify(Subject & whoFrom) {
//	cout << "Notified" << endl;
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
	} else if ((currCol > recCol) && (currRow > recRow)) {
		direction = Direction::SE;
		revDir = Direction::NW;
	}	
	if (recState.type == StateType::PieceAdded) {
		//cout << "Piece Added" << endl;
		State nState{StateType::Relay, direction, true, recState.piece};
		setState(nState);
		addAttacker(recState.piece->getIsWhite(), recState.piece);
		notifyObservers();
	} else if (recState.type == StateType::PieceRemoved) {	
		//cout << "Piece Removed" << endl;
		State nState{StateType::Relay, direction, false, recState.piece};
		setState(nState);
		removeAttacker(recState.piece->getIsWhite(), recState.piece->getId());
		notifyObservers();
	} else if (recState.type == StateType::Relay) {
		//cout << "Relay" << endl;
		if (direction == recState.direction) {
			if (getPiece() == nullptr) {
				State nState{StateType::Relay, direction, recState.attacked, recState.piece};
				setState(nState);
				if (recState.attacked) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				} else {
					removeAttacker(recState.piece->getIsWhite(), recState.piece->getId());
				}
				notifyObservers();
			} else if (getPiece() != nullptr) {			
				State nState{StateType::Reply, revDir, true, getPiece()};
				setState(nState);	
				if (recState.attacked) {
					addAttacker(recState.piece->getIsWhite(), recState.piece);
				} else {
					removeAttacker(recState.piece->getIsWhite(), recState.piece->getId());
				}
				notifyObservers();
			}
		}
	} else if (recState.type == StateType::Reply) {
		//cout << "Reply" << endl;
		if (direction == recState.direction) {
			if (getPiece() == nullptr) {
				State nState{StateType::Reply, direction, false, recState.piece};
				setState(nState);	
				addAttacker(recState.piece->getIsWhite(), recState.piece);
				notifyObservers();
			} else if (getPiece() != nullptr) {			
				State nState{StateType::Reply, direction, true, getPiece()};
				setState(nState);
				addAttacker(recState.piece->getIsWhite(), recState.piece);
				notifyObservers();
			}
		}
	}
}



