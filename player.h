#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <string>
#include <memory>
using namespace std;

class Piece;

class Player {
	map<string, shared_ptr<Piece>> pieces;
	bool isWhite;
	int score;
	public:
		Player(bool isWhite); 
		virtual void makeMove() = 0;
		bool isInCheck() const;
		void addPiece(shared_ptr<Piece>);
		void removePiece(string id);
};

class Human: public Player {
	public:
		Human(bool isWhite);
		void makeMove() override;
};

class Level1: public Player {
        public:
		Level1(bool isWhite);
                void makeMove() override;
};

class Level2: public Player {
        public:
		Level2(bool isWhite);
                void makeMove() override;
};

class Level3: public Player {
        public:
		Level3(bool isWhite);
                void makeMove() override;
};

class Level4: public Player {
        public:
		Level4(bool isWhite);
                void makeMove() override;
};

#endif
