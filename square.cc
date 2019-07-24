#include "square.h"
#include "piece.h"
using namespace std;


Square::Square(int r, int c, shared_ptr<Piece> currPiece): r{r}, c{c}, currPiece{currPiece} {
	wAttacks = {};
	bAttacks = {};
}
