#ifndef PIECE_H
#define PIECE_H

// Relevant forward declarations and includes
#include <string>
#include <utility> //for pair
#include <stdlib.h> //for abs 
using namespace std;

class Piece {
	int row;
	int col;
	bool isWhite;
	string id;
	int movesMade;
	public:
		pair<int,int> getCoor();
		void changeCoor(int r, int c);
		bool getIsWhite();
		string getId();
		int getMovesMade();
		Piece(int row, int col, bool isWhite, string id, int movesMade);
		virtual void move(int r, int c, bool cover, bool between) = 0;

};

class Pawn final: public Piece {
	bool specialAdvance;
	public:
		Pawn(int row, int col, bool isWhite, string id, int movesMade = 0, bool specialAdvance = false);
		void move(int r, int c, bool cover, bool between) override;
};

class Knight final: public Piece {
        public:
                Knight(int row, int col, bool isWhite, string id, int movesMade = 0);
		void move(int r, int c, bool cover, bool between) override;
};

class Bishop final: public Piece {
        public:
                Bishop(int row, int col, bool isWhite, string id, int movesMade = 0);
		void move(int r, int c, bool cover, bool between) override;
};

class Rook final: public Piece {
        public:
                Rook(int row, int col, bool isWhite, string id, int movesMade = 0);
		void move(int r, int c, bool cover, bool between) override;
};

class Queen final: public Piece {
        public:
                Queen(int row, int col, bool isWhite, string id, int movesMade = 0);
		void move(int r, int c, bool cover, bool between) override;
};

class King final: public Piece {
        public:
                King(int row, int col, bool isWhite, string id, int movesMade = 0);
		void move(int r, int c, bool cover, bool between) override;
};

#endif
