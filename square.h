#ifndef SQUARE_H
#define SQUARE_H

////// Relevant forward declarations and includes
#include <vector>
using namespace std;

class Piece;

class Square {
	vector<Piece> wAttacks;
	vector<Piece> bAttacks;
	shared_ptr<Piece> currPiece;
//	Piece * currPiece;
	int r;
	int c;
	
	public:
		shared_ptr<Piece> getPiece() const;
		void setPiece(shared_ptr<Piece> piece);
		Square(int r, int c, shared_ptr<Piece> currPiece);  
		//void notify() override;
};
#endif
