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

pair<int,int> Square::getCoords() const {
	return make_pair(r, c);
}

void Square::notify(Subject & whoFrom) {
	State recState = whoFrom.getState();
	

}
