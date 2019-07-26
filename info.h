#ifndef INFO_H
#define INFO_H

#include <utility>

class Piece;

struct Info {
	pair<int, int> coords;
	shared_ptr<Piece> piece;
	bool wAttacked;
	bool bAttacked;
};


#endif
