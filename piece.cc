#include "piece.h"
using namespace std;

Piece::Piece(int row, int col, bool isWhite, string id, int movesMade): 
	row{row}, col{col}, isWhite{isWhite}, id{id}, movesMade{movesMade} {}

pair<int,int> Piece::getCoor() {
	return make_pair(row, col); 
}

void Piece::changeCoor(int r, int c) {
	row = r;
	col = c;
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

void Pawn::move(int r, int c, bool cover) {
	pair<int,int> currCoor = getCoor();
        int movesMade = getMovesMade();
	if (r < 0 || r > 7 || c < 0 || c > 7 || cover) {
                throw;  
        }
	int dir = 1;
	if (!getIsWhite()) {
		dir = -1;	
	}
	if (currCoor.first - r == dir * 1 && currCoor.second - c == 0) {
                changeCoor(r, c);
	} else if ((movesMade == 0) && (currCoor.first - r == dir * 2 && currCoor.second - c == 0)) {
		changeCoor(r, c);
	} else if ((currCoor.first - r == dir * 1 && abs(currCoor.second - c == 1)) && cover) {
		changeCoor(r, c);
	} else {
		throw;
	}
}

Knight::Knight(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Knight::move(int r, int c, bool cover) {
	pair<int,int> currCoor = getCoor();
	if (r < 0 || r > 7 || c < 0 || c > 7 || cover) {
		throw;
	}
	if ((abs(currCoor.first - r) == 2 && abs(currCoor.second - c) == 1) ||
	    (abs(currCoor.first - r) == 1 && abs(currCoor.second - c) == 2)) {
		changeCoor(r, c);
	} else {
		throw;
	}
}

Bishop::Bishop(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Bishop::move(int r, int c, bool cover) {
	pair<int,int> currCoor = getCoor();
        if (r < 0 || r > 7 || c < 0 || c > 7 || cover) {
                throw;
        }
	if ((abs(currCoor.first - r) == abs(currCoor.second - c)) &&
	    (abs(currCoor.first - r) > 0)) {
		changeCoor(r, c);
	} else {
		throw;
	}
}

Rook::Rook(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Rook::move(int r, int c, bool cover) {
	pair<int,int> currCoor = getCoor();
        if (r < 0 || r > 7 || c < 0 || c > 7 || cover) {
                throw;
        }
	if ((abs(currCoor.first - r) == 0 && abs(currCoor.second - c) > 0) ||
            (abs(currCoor.first - r) > 0 && abs(currCoor.second - c) == 0)) {
                changeCoor(r, c);
        } else {
                throw;
        }
}

Queen::Queen(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Queen::move(int r, int c, bool cover) {
	pair<int,int> currCoor = getCoor();
        if (r < 0 || r > 7 || c < 0 || c > 7 || cover) {
                throw;
        }
	if (((abs(currCoor.first - r) == abs(currCoor.second - c)) &&
             (abs(currCoor.first - r) > 0)) ||
	    ((abs(currCoor.first - r) == 0 && abs(currCoor.second - c) > 0) ||
             (abs(currCoor.first - r) > 0 && abs(currCoor.second - c) == 0))) {
		changeCoor(r, c);
	} else {
		throw;
	}
}

King::King(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void King::move(int r, int c, bool cover) {
	pair<int,int> currCoor = getCoor();
        if (r < 0 || r > 7 || c < 0 || c > 7 || cover) {
                throw;
        }
	if ((currCoor.first - r) * (currCoor.first - r) + (currCoor.second - c) * (currCoor.second - c) <= 2) {
		changeCoor(r, c);
	} else {
		throw;
	}
}
