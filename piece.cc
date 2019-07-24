#include "piece.h"
using namespace std;

<<<<<<< HEAD
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
=======
<<<<<<< HEAD
Piece::Piece(int row, int col, string id, bool isWhite, int movesMade): 
	row {row}, col {col}, id {id}, isWhite {isWhite}, movesMade {movesMade} {};
=======
Piece(int row, int col, int movesMade, bool isWhite, string id);
	row {row}, col {col}, movesMade {movesMade}, isWhite {isWhite}, id {id} {};
>>>>>>> 3b16f3ec1d140829028b45118f0d4837137b17b9
>>>>>>> a4aa4d5cf1cfbfd4facac90feef4044122e2b2a9
