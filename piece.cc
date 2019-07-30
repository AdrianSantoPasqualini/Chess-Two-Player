#include "piece.h"
using namespace std;

Piece::Piece(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant):
	row{row}, col{col}, isWhite{isWhite}, id{id}, movesMade{movesMade}, castle{castle}, enPassant{enPassant} {}

pair<int,int> Piece::getCoor() {
	return make_pair(row, col); 
}

void Piece::updatePiece(int r, int c) {
	row = r;
	col = c;
	movesMade++;
}

void Piece::decrementMoves(int d) {
	movesMade -= d;
}

bool Piece::getIsWhite() {
	return isWhite;
}

string Piece::getId() {
	return id;
}

int Piece::getMovesMade() {
	return movesMade;
}

int Piece::getCastle() {
	return castle;
}

void Piece::changeCastle(int c) {
	castle = c;
}

int Piece::getEnPassant() {
	return enPassant;
}

void Piece::changeEnPassant(int p) {
	enPassant = p;
}

Pawn::Pawn(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant): 
	Piece{row, col, isWhite, id, movesMade, castle, enPassant} {}

bool Pawn::move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) {
	pair<int,int> currCoor = getCoor();
        int movesMade = getMovesMade();
	string msg = "";
	if ((pieceOnSq && currCoor.second == c) || blocked) {
		msg = "Pawn is blocked.";
                throw msg;
        }
	int dir = 1;
	if (!getIsWhite()) {
		dir = -1;	
	}
	if (currCoor.first - r == dir * 1 && currCoor.second - c == 0) {
		return true;
	} else if ((movesMade == 0) && (currCoor.first - r == dir * 2 && currCoor.second - c == 0)) {
		changeEnPassant(moves);
		return true;
	} else if ((currCoor.first - r == dir * 1 && abs(currCoor.second - c) == 1) && pieceOnSq) {
		return true;
	} else if ((currCoor.first - r == dir * 1 && abs(currCoor.second - c) == 1) && (getEnPassant() == moves - 1 && moves > 3)) {
		return true;
	} else {
		msg = "Invalid pawn movement.";
		throw msg;
	}
	return false;
}

Knight::Knight(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant):
        Piece{row, col, isWhite, id, movesMade, castle, enPassant} {}

bool Knight::move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
	if (blocked) {
		msg = "Knight is blocked.";
		throw msg;
	}
	if ((abs(currCoor.first - r) == 2 && abs(currCoor.second - c) == 1) ||
	    (abs(currCoor.first - r) == 1 && abs(currCoor.second - c) == 2)) {
		return true;
	} else {
		msg = "Invalid knight movement.";
		throw msg;
	}
	return false;
}

Bishop::Bishop(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant):
        Piece{row, col, isWhite, id, movesMade, castle, enPassant} {}

bool Bishop::move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
        if (blocked) {
		msg = "Bishop is blocked.";
		throw msg;	
	}
	if ((abs(currCoor.first - r) == abs(currCoor.second - c)) &&
	    (abs(currCoor.first - r) > 0)) {
		return true;
	} else {
		msg = "Invalid bishop movement.";
		throw msg;
	}
	return false;
}

Rook::Rook(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant):
        Piece{row, col, isWhite, id, movesMade, castle, enPassant} {}

bool Rook::move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
        if (blocked) {
		msg = "Rook is blocked.";
        	throw msg;
	}
	if ((abs(currCoor.first - r) == 0 && abs(currCoor.second - c) > 0) ||
            (abs(currCoor.first - r) > 0 && abs(currCoor.second - c) == 0)) {
                return true;
        } else {
		msg = "Invalid rook movement.";
        	throw msg;
	}
	return false;
}

Queen::Queen(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant):
        Piece{row, col, isWhite, id, movesMade, castle, enPassant} {}

bool Queen::move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
        if (blocked) {
		msg = "Queen is blocked.";
        	throw msg;
	}
	if (((abs(currCoor.first - r) == abs(currCoor.second - c)) &&
             (abs(currCoor.first - r) > 0)) ||
	    ((abs(currCoor.first - r) == 0 && abs(currCoor.second - c) > 0) ||
             (abs(currCoor.first - r) > 0 && abs(currCoor.second - c) == 0))) {
		return true;
	} else {
		msg = "Invalid queen movement.";
		throw msg;
	}
	return false;
}

King::King(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant):
        Piece{row, col, isWhite, id, movesMade, castle, enPassant} {}

bool King::move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) {
	pair<int,int> currCoor = getCoor();
	string msg;
	if (moveIntoAttack) {
		msg = "King cannot move onto a square that is under attack.";
		throw msg;
	}
	if (blocked) {
		msg = "King is blocked or will be under check.";
		throw msg;
	}
	if ((currCoor.first - r) * (currCoor.first - r) + (currCoor.second - c) * (currCoor.second - c) <= 2) {
		return true;
	} else if (!pieceOnSq) {
		if ((r == 0 || r == 7) && c == 6) {
			if (checked) {
				msg = "King is under check.";
				throw msg;
			} else if (getMovesMade() == 0) {
				changeCastle(1);
			} else {
				msg = "King cannot castle, king has already moved.";
				throw msg;
			}
		} else if ((r == 0 || r == 7) && c == 2) {
			if (checked) {
				msg = "King is under check.";
				throw msg;
			} else if (getMovesMade() == 0) {
				changeCastle(2);
			} else {
				msg = "King cannot castle, king has already moved.";
				throw msg;
			}
		}
	} else if (pieceOnSq) {
		msg = "King cannot castle, enemy piece on square.";
		throw msg;
	} else {
		msg = "Invalid king movement.";
		throw msg;
	}
	return false;
}	
