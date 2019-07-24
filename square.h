#ifndef SQUARE_H
#define SQUARE_H

////// Relevant forward declarations and includes
#include <vector>
using namespace std;

class Piece;

class Square {
	vector<Piece> wAttacks;
	vector<Piece> bAttacks;
//	shared_ptr<Piece> currPiece;
	Piece * currPiece;
	int r;
	int c;
	
	public:
		Piece * getPiece() const;
		Square(int r, int c, Piece * currPiece);  
		//void notify() override;
};
#endif
