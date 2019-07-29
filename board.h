#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm> // for find
#include "square.h"
#include "window.h"
////////////////////////////////
// try forward declarations first. Only if they dont work, include the .h file
///////////////////////////////
using namespace std;

class Player;

class Board {
	vector<vector<Square>> defSquares;
	vector<int> whiteCounts;
	vector<int> blackCounts;
	bool defWhitesTurn;
	vector<vector<Square>> squares;
	Xwindow window;
	unique_ptr<Player> player1;
	unique_ptr<Player> player2;
	bool whitesTurn;
	int whiteScore;
	int blackScore;

	// private methods
	Board(vector<vector<Square>>);
	void drawPiece(shared_ptr<Piece> piece);
	void undrawPiece(int r, int c);
	void drawScore();
	void printDefault();
	public:
		Board();
		void draw();
		void setPlayer(string colour, string type);
		void init();
		void setup();
		int whoWon();
		void incWhiteScore();
		void incBlackScore();
		int getWhiteScore();
		int getBlackScore();
		bool isWhitesTurn();
		shared_ptr<Square> getSquare(int r, int c);
		void movePiece(int curR, int curC, int newR, int newC);
		void updateTurn(int curR, int curC, int newR, int newC, shared_ptr<Piece> piece);
		friend ostream & operator<<(ostream &out, const Board &b); 
};

#endif
