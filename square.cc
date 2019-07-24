#include "square.h"
#include "piece.h"
using namespace std;


Square::Square(int r, int c, Piece * currPiece): r{r}, c{c}, currPiece{currPiece} {}

Piece * Square::getPiece() const {
	return currPiece;
}
