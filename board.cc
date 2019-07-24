#include "board.h"
using namespace std;


void Board::init(string playerOne, string playerTwo) {
	whitesTurn = true;
	squares.clear();
	for (int r = 0; i < 8; i++) {
		for (int c = 0; c < 8; c++) {
			squares[r].emplace_back(Square(r,c));
		}
	}
}

