#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include "square.h"
////////////////////////////////
// try forward declarations first. Only if they dont work, include the .h file
///////////////////////////////
using namespace std;


class Player;

class Board {
	vector<vector<Square>> squares;
	//Xwindow window;
	unique_ptr<Player> player1;
	unique_ptr<Player> player2;
	bool whitesTurn;
	int whiteScore;
	int blackScore;
	public:
		//~Board();
		void setPlayer(string colour, string type);
		void init();
		void setup();
		void movePiece(int curR, int curC, int newR, int newC);
		int whoWon();
		void incWhiteScore();
		void incBlackScore();
		bool isWhitesTurn();
		void updateTurn(int curR, int curC, int newR, int newC, shared_ptr<Piece> piece);
		friend ostream & operator<<(ostream &out, const Board &b); 
};

#endif
