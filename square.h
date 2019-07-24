#ifndef SQUARE_H
#define SQUARE_H

////// Relevant forward declarations and includes

using namespace std;

class Piece;

class Square {
	vector<Piece> wAttacks;
	vector<Piece> bAttacks;
	shared_ptr<Piece> currPiece;
	int r;
	int c;
	
	public:
		Square(int r, int c, shared_prt<Piece> currPiece);  
		void notify() override;
}
#endif
