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

#endif
