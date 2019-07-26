#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <string>
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
};

class Human final: public Player {
	public:
		Human(bool isWhite);
		void makeMove() override;
};

class Level1 final: public Player {
        public:
		Level1(bool isWhite);
                void makeMove() override;
};

class Level2 final: public Player {
        public:
		Level2(bool isWhite);
                void makeMove() override;
};

class Level3 final: public Player {
        public:
		Level3(bool isWhite);
                void makeMove() override;
};

class Level4 final: public Player {
        public:
		Level4(bool isWhite);
                void makeMove() override;
};

#endif
