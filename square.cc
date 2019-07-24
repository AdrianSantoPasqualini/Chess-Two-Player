#include "square.h"
#include "piece.h"
using namespace std;


Square::Square(int r, int c, shared_ptr<Piece> currPiece): currPiece{currPiece}, r{r}, c{c} {}

shared_ptr<Piece> Square::getPiece() const {
	return currPiece;
}

void Square::setPiece(shared_ptr<Piece> piece) {
	currPiece = piece;
}
