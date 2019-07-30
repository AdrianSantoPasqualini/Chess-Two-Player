#ifndef PIECE_H
#define PIECE_H

// Relevant forward declarations and includes
#include <string>
#include <utility> //for pair
#include <stdlib.h> //for abs 
#include <memory>
#include <iostream>
using namespace std;

class Piece {
	int row;
	int col;
	bool isWhite;
	string id;
	int movesMade;
	int castle;
	int enPassant;
	public:
		pair<int,int> getCoor();
		void updatePiece(int r, int c);
		void decrementMoves(int d);
		bool getIsWhite();
		string getId();
		int getMovesMade();
		int getCastle();
		void changeCastle(int c);
		int getEnPassant();
		void changeEnPassant(int p);
		Piece(int row, int col, bool isWhite, string id, int movesMade, int castle, int enPassant);
		virtual bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) = 0;
};

class Pawn final: public Piece {
	public:
		Pawn(int row, int col, bool isWhite, string id, int movesMade = 0, int castle = 0, int enPassant = 0);
		bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) override;
};

class Knight final: public Piece {
        public:
                Knight(int row, int col, bool isWhite, string id, int movesMade = 0, int castle = 0, int enPassant = 0);
		bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) override;
};

class Bishop final: public Piece {
        public:
                Bishop(int row, int col, bool isWhite, string id, int movesMade = 0, int castle = 0, int enPassant = 0);
		bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) override;
};

class Rook final: public Piece {
        public:
                Rook(int row, int col, bool isWhite, string id, int movesMade = 0, int castle = 0, int enPassant = 0);
		bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) override;
};

class Queen final: public Piece {
        public:
                Queen(int row, int col, bool isWhite, string id, int movesMade = 0, int castle = 0, int enPassant = 0);
		bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) override;
};

class King final: public Piece {
	public:
                King(int row, int col, bool isWhite, string id, int movesMade = 0, int castle = 0, int enPassant = 0);
		bool move(int r, int c, int moves, bool pieceOnSq, bool blocked, bool moveIntoAttack, bool checked) override;
};

#endif
