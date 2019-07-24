#ifndef PIECE_H
#define PIECE_H

// Relevant forward declarations and includes
#include <string>
using namespace std;

class Piece {
	int row;
	int col;
	int movesMade;
	bool isWhite;
	string id;

	public:
		string getId() {
			return id;
		}
		
		Piece(int row, int col, int movesMade = 0, bool isWhite, string id);
		virtual void move(int r, int c) = 0;

};

class Pawn: public Piece {
	bool specialAdvance;
	
	public:
		Pawn(int row, int col, int movesMade = 0, bool isWhite, string id, bool specialAdvance = false);
		void move(int r, int c) override;
};

class Knight: public Piece {
        public:
                Knight(int row, int col, int movesMade = 0, bool isWhite, string id);
		void move(int r, int c) override;
};

class Bishop: public Piece {
        public:
                Bishop(int row, int col, int movesMade = 0, bool isWhite, string id);
		void move(int r, int c) override;
};

class Rook: public Piece {
        public:
                Rook(int row, int col, int movesMade = 0, bool isWhite, string id);
		void move(int r, int c) override;
};

class Queen: public Piece {
        public:
                Queen(int row, int col, int movesMade = 0, bool isWhite, string id);
		void move(int r, int c) override;
};

class King: public Piece {
        public:
                King(int row, int col, int movesMade = 0, bool isWhite, string id);
		void move(int r, int c) override;
};

#endif
