#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <utility> //To get pair
#include <memory>
#include "piece.h"
#include "observer.h"
#include "subject.h"
using namespace std;

class Square: public Subject, public Observer  {
	vector<shared_ptr<Piece>> wAttacks;
	vector<shared_ptr<Piece>> bAttacks;
	shared_ptr<Piece> currPiece;
	int r;
	int c;
	
	public:
		shared_ptr<Piece> getPiece() const;
		pair<int,int> getCoords() const;
		void setPiece(shared_ptr<Piece> piece);
		void removeAttacker(bool white, string id);
		void addAttacker(bool white, shared_ptr<Piece> piece);
		void toggleAttacker(bool attacked, shared_ptr<Piece> piece);
		Square(int r, int c, shared_ptr<Piece> currPiece);  
		Square(const Square & other);
		void notify(Subject & whoFrom) override;
		Info getInfo() const override;
};
#endif
