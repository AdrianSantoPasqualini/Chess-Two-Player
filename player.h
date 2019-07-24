#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <string>

class Player {
	public:
		map<string, Piece> pieces;
		bool isWhite;
		Player(map<string,Piece> pieces, bool isWhite); 
		virtual void makeMove() = 0;
		bool isInCheck();
};

class Human: public Player {
	public:
		void makeMove() override;
}

class Level1: public Player {
        public:
                void makeMove() override;
}

class Level2: public Player {
        public:
                void makeMove() override;
}

class Level3: public Player {
        public:
                void makeMove() override;
}

class LevelN: public Player {
        public:
                void makeMove() override;
}

#endif
