#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <stdlib.h> //for abs
#include "move.h"
using namespace std;

class Piece;
class Board;


class Player {
	map<string, shared_ptr<Piece>> pieces;
	bool isWhite;
	int score;
	protected:
		Board *board;
		vector<Move> legalMoves;
	public:
		Player(bool isWhite);
		virtual ~Player() {};
		virtual void makeMove() = 0;
		bool isInCheck() const;
		int howManyLegalMoves();
		void clearPieces();
		void addPiece(shared_ptr<Piece>);
		void removePiece(string id);
		void attachBoard(Board * board);
		void generateLegalMoves();
};

class Human final: public Player {
	public:
		~Human() {}
		Human(bool isWhite);
		void makeMove() override;
};

class Level1 final: public Player {
        public:
		~Level1() {}
		Level1(bool isWhite);
                void makeMove() override;
};

class Level2 final: public Player {
        public:
		~Level2() {}
		Level2(bool isWhite);
                void makeMove() override;
};

class Level3 final: public Player {
        public:
		~Level3() {}
		Level3(bool isWhite);
                void makeMove() override;
};

class Level4 final: public Player {
        public:
		~Level4() {}
		Level4(bool isWhite);
                void makeMove() override;
};

#endif
