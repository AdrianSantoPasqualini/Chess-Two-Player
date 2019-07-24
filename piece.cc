#include "piece.h"
using namespace std;

Piece::Piece(int row, int col, bool isWhite, string id, int movesMade): 
	row{row}, col{col}, isWhite{isWhite}, id{id}, movesMade{movesMade} {}

Pawn::Pawn(int row, int col, bool isWhite, string id, int movesMade, bool specialAdvance): 
	Piece{row, col, isWhite, id, movesMade}, specialAdvance {specialAdvance} {}

void Pawn::move(int r, int c) {
	
}

Knight::Knight(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Knight::move(int r, int c) {

}

Bishop::Bishop(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Bishop::move(int r, int c) {

}

Rook::Rook(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Rook::move(int r, int c) {

}

Queen::Queen(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void Queen::move(int r, int c) {

}

King::King(int row, int col, bool isWhite, string id, int movesMade):
        Piece{row, col, isWhite, id, movesMade} {}

void King::move(int r, int c) {

}
