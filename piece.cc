#include "piece.h"
using namespace std;

Piece::Piece(int row, int col, bool isWhite, string id, int movesMade): 
	row{row}, col{col}, isWhite{isWhite}, id{id}, movesMade{movesMade} {}

pair<int,int> Piece::getCoor() {
	return make_pair(row, col); 
}

void Piece::updatePiece(int r, int c) {
	row = r;
	col = c;
	movesMade++;
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

Pawn::Pawn(int row, int col, bool isWhite, string id, int movesMade, bool specialAdvance): 
	Piece{row, col, isWhite, id, movesMade}, specialAdvance {specialAdvance} {}

void Pawn::move(int r, int c, bool pieceOnSq, bool blocked) {
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
                updatePiece(r, c);
	} else if ((movesMade == 0) && (currCoor.first - r == dir * 2 && currCoor.second - c == 0)) {
		updatePiece(r, c);
		specialAdvance = true;
	} else if ((currCoor.first - r == dir * 1 && abs(currCoor.second - c) == 1) && pieceOnSq) {
		updatePiece(r, c);
	} else {
		msg = "Invalid pawn movement.";
		throw msg;
	}
}

Knight::Knight(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Knight::move(int r, int c, bool pieceOnSq, bool blocked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
	if ((abs(currCoor.first - r) == 2 && abs(currCoor.second - c) == 1) ||
	    (abs(currCoor.first - r) == 1 && abs(currCoor.second - c) == 2)) {
		updatePiece(r, c);
	} else {
		msg = "Invalid knight movement.";
		throw msg;
	}
}

Bishop::Bishop(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Bishop::move(int r, int c, bool pieceOnSq, bool blocked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
        if (blocked) {
		msg = "Bishop is blocked.";
		throw msg;	
	}
	if ((abs(currCoor.first - r) == abs(currCoor.second - c)) &&
	    (abs(currCoor.first - r) > 0)) {
		updatePiece(r, c);
	} else {
		msg = "Invalid bishop movement.";
		throw msg;
	}
}

Rook::Rook(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Rook::move(int r, int c, bool pieceOnSq, bool blocked) {
	pair<int,int> currCoor = getCoor();
	string msg = "";
        if (blocked) {
		msg = "Rook is blocked.";
        	throw msg;
	}
	if ((abs(currCoor.first - r) == 0 && abs(currCoor.second - c) > 0) ||
            (abs(currCoor.first - r) > 0 && abs(currCoor.second - c) == 0)) {
                updatePiece(r, c);
        } else {
		msg = "Invalid rook movement.";
        	throw msg;
	}
}

Queen::Queen(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Queen::move(int r, int c, bool pieceOnSq, bool blocked) {
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
		updatePiece(r, c);
	} else {
		msg = "Invalid queen movement.";
		throw msg;
	}
}

King::King(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void King::move(int r, int c, bool pieceOnSq, bool blocked) {
	pair<int,int> currCoor = getCoor();
	string msg;
        if (blocked) {
		msg = "King is blocked or will be under check.";
		throw msg;
	}
	if ((currCoor.first - r) * (currCoor.first - r) + (currCoor.second - c) * (currCoor.second - c) <= 2) {
		updatePiece(r, c);
	} else {
		msg = "Invalid king movement.";
		throw msg;
	}
}
