#include "piece.h"
using namespace std;

Piece::Piece(int row, int col, int movesMade, bool isWhite, string id):
	row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {}

Pawn::Pawn(int row, int col, int movesMade, bool isWhite, string id, bool specialAdvance):
	row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id}, specialAdvance {specialAdvance} {}

void Pawn::move(int r, int c) {
	
}

Knight::Knight(int row, int col, int movesMade, bool isWhite, string id):
        row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {}

void Knight::move(int r, int c) {

}

Bishop::Bishop(int row, int col, int movesMade, bool isWhite, string id):
        row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {}

void Bishop::move(int r, int c) {

}

Rook::Rook(int row, int col, int movesMade, bool isWhite, string id):
        row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {}

void Rook::move(int r, int c) {

}

Queen::Queen(int row, int col, int movesMade, bool isWhite, string id):
        row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {}

void Queen::move(int r, int c) {

}

King::King(int row, int col, int movesMade, bool isWhite, string id):
        row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {}

void King::move(int r, int c) {

}
