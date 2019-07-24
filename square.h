#ifndef SQUARE_H
#define SQUARE_H

////// Relevant forward declarations and includes

using namespace std;

class Square {
	vector<Piece> wAttacks;
	vector<Piece> bAttacks;
	Piece currPiece;
	int r;
	int c;
	
	public:
		void notify() override;
}
#endif
