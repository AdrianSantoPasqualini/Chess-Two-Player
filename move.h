#ifndef MOVE_H
#define MOVE_H

#include <utility>
using namespace std;

class Piece;

struct Move {
	pair<int, int> nCoords;
	shared_ptr<Piece> piece;
	bool toCheck;
	bool toCapture;
	bool toAvoid;
};
#endif
